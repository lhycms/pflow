from abc import ABC, abstractclassmethod
import numpy as np

from ...io.publicLayer.neigh import StructureNeighborsV1


class DpFeaturePairPremiseDescriptor(object):
    '''
    Description
    -----------
        1. Map str to Derived class of `StructureNeighborBase`.
    
    Usage
    -----
        1. Demo 1.
            ```python
            dppd = DpFeaturePairPremiseDescription("v1")
            ```
    
    ----
        1. 'v1': `DpFeaturePairPremise`
            - for `StructureNeighborsV1`
    '''
    registry = {}

    @classmethod
    def register(cls, name:str):
        def wrapper(subclass:DpFeaturePairPremiseBase):
            cls.registry[name] = subclass
        return wrapper
    
    
    @classmethod
    def create(cls, name:str, *args, **kwargs):
        subclass = cls.registry[name]
        if subclass is None:
            raise ValueError(f"No DpFeaturePairPremise registered with name '{name}'")
        return subclass(*args, **kwargs)
    


class DpFeaturePairPremiseBase(ABC):
    @abstractclassmethod
    def extract_feature_pair(self):
        pass
    
    

@DpFeaturePairPremiseDescriptor.register("v1")
class DpFeaturePairPremiseV1(DpFeaturePairPremiseBase):
    def __init__(
                self,
                structure_neighbors:StructureNeighborsV1,
                ):
        self.structure_neighbors = structure_neighbors
        self.max_num_nbrs_real = structure_neighbors.key_nbr_atomic_numbers.shape[1]
    
    
    def extract_feature_pair(
                self,
                center_atomic_number:int,
                nbr_atomic_number:int):
        '''
        Description
        -----------
            1. 根据以下几个条件筛选所需要的信息：
                1.1. `中心原子的元素种类`
                1.2. `近邻原子的元素种类`
                1.3. `排除中心原子`
                1.4. `最大近邻原子数` (对于一种近邻元素来说)，决定了 zero_padding 的尺寸
        
        Parameters
        ----------
            1. center_atomic_number: int
                - 中心原子的原子序数
            2. nbr_atomic_number: int
                - 近邻原子的原子序数
        '''
        ### Step 1. 根据中心原子的原子序数，设置筛选条件 -- `mask_center`
        ### Step 1.1. 根据中心原子的原子序数的筛选条件
        mask_center = (self.structure_neighbors.key_nbr_atomic_numbers[:, 0] == center_atomic_number)
        mask_center = np.array(mask_center).reshape(-1, 1)
        mask_center = np.repeat(mask_center, self.max_num_nbrs_real, axis=1)
        ### Step 1.2. 根据近邻原子的原子序数的筛选条件
        mask_nbr = (self.structure_neighbors.key_nbr_atomic_numbers == nbr_atomic_number)
        ### Step 1.3. 获取上述筛选条件的 &
        mask_total = mask_center & mask_nbr
        ### Step 1.4. 排除中心原子自身
        # shape = (num_centers, max_num_nbrs_real)
        '''
        [[False False False False False False False False False False False False False]
        [False False False False False False False False False False False False False]
        [False False False False False False False False False False False False False]
        [False False False False False False False False False False False False False]
        [False False False False False False False False False False False False False]
        [False False False False False False False False False False False False False]
        [False False False False False False False False False False False False False]
        [False False False False False False False False False False False False False]
        [False False False False False False False  True  True  True  True  True True]
        [False False False False False False False  True  True  True  True  True True]
        [False False False False False False False  True  True  True  True  True True]
        [False False False False False False False  True  True  True  True  True True]]
        '''
        mask_total[:, 0] = False
        #print(mask_total)
        
        ### Step 2.
        setattr( self, "num_centers", np.count_nonzero(np.count_nonzero(mask_total, axis=1)) )
        setattr( self, "max_num_nbrs_real_element", np.max(np.count_nonzero(mask_total, axis=1)))
        
        ### Step 3. 初始化返回的数组 (这些数组都不包括中心原子自身)
        #       1. `dp_feature_pair_an`:
        #       2. `dp_feature_pair_d`:
        #       3. `dp_feature_pair_rc`:
        dp_feature_pair_an = np.zeros((self.num_centers, self.max_num_nbrs_real_element))
        dp_feature_pair_d = np.zeros((self.num_centers, self.max_num_nbrs_real_element))
        dp_feature_pair_rc = np.zeros((self.num_centers, self.max_num_nbrs_real_element, 3))

        ### Step 4. 计算相对坐标
        center_coords = self.structure_neighbors.key_nbr_coords[:, 0, :]
        center_coords = np.repeat(
                            center_coords[:, np.newaxis, :],
                            1,
                            axis=1)
        # shape = (num_centers, max_num_nbrs_max+1, 3) = (12, 13, 3)
        relative_coords = self.structure_neighbors.key_nbr_coords - center_coords
        
        ### Step 5. 根据筛选条件 `mask_total` 填充 Step 3 的三个数组
        real_center_i = 0
        for tmp_i in range(mask_total.shape[0]):
            tmp_num_nbrs = np.count_nonzero(mask_total[tmp_i, :])
            if tmp_num_nbrs == 0:
                '''
                0; 0; 0; 0; 0; 0; 0; 0; 6; 6; 6; 6
                '''
                continue
            dp_feature_pair_an[real_center_i, :tmp_num_nbrs] = self.structure_neighbors.key_nbr_atomic_numbers[tmp_i][mask_total[tmp_i, :]]
            dp_feature_pair_d[real_center_i, :tmp_num_nbrs] = self.structure_neighbors.key_nbr_distances[tmp_i][mask_total[tmp_i, :]]
            dp_feature_pair_rc[real_center_i, :tmp_num_nbrs, :] = relative_coords[tmp_i][mask_total[tmp_i, :]]
            real_center_i += 1
        
        return dp_feature_pair_an, dp_feature_pair_d, dp_feature_pair_rc