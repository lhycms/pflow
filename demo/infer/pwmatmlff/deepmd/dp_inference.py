from matersdk.io.pwmat.output.movement import Movement
from matersdk.data.deepmd.data_system import DpLabeledSystem
from matersdk.feature.deepmd.preprocess import TildeRNormalizer
from matersdk.infer.pwmatmlff.deepmd.inference import DpInfer



### Step 0. 自定义参数
movement_path = "/data/home/liuhanyu/hyliu/code/mlff/test/demo2/PWdata/data1/MOVEMENT"  # 产生训练集、验证集的 MOVEMENT
pt_file_path = "/data/home/liuhanyu/hyliu/code/mlff/PWmatMLFF_dev/test/demo2/record/checkpoint.pt"
device = "cuda:0"
rcut = 6.0                      # Rmax
rcut_smooth = 5.5               # Rmin
scaling_matrix = [3, 3, 3]      # 三维体系：[3, 3, 3]; 二维体系: [3, 3, 1]
davg = None                     # 设置为 None 时，可以从 MOVEMENT 自动计算
dstd = None                     # 设置为 None 时，可以从 MOVEMENT 自动计算
center_atomic_numbers = [3, 14] # 体系内所有元素的原子序数，从小到大排列
nbr_atomic_numbers = [3, 14] # 体系内所有元素的原子序数，从小到大排列
max_num_nbrs = [100, 100]    # 近邻原子的最大数目，与 nbr_atomic_numbers 对应
reformat_mark = True            # 永远都是True
coords_are_cartesian = True # 永远都是True
movement = Movement(movement_path=movement_path)
new_structure = movement.get_frame_structure(idx_frame=500) # 需要做 inference 的结构


### Step 1. 计算 `davg`, `dstd`

### Step 1.1. 计算 Rij 的 davg, dstd
dpsys = DpLabeledSystem.from_trajectory_s(trajectory_object=movement)
tildeR_normalizer = TildeRNormalizer.from_dp_labeled_system(
                    dp_labeled_system=dpsys,
                    structure_indices=[*(range(10))],
                    rcut=rcut,
                    rcut_smooth=rcut_smooth,
                    center_atomic_numbers=center_atomic_numbers,
                    nbr_atomic_numbers=nbr_atomic_numbers,
                    max_num_nbrs=max_num_nbrs,
                    scaling_matrix=scaling_matrix
)
davg, dstd = tildeR_normalizer.davgs, tildeR_normalizer.dstds


### Step 2. 
dp_infer = DpInfer(
    pt_file_path=pt_file_path,
    device=device,
    rcut=rcut,
    rcut_smooth=rcut_smooth,
    davg=davg,
    dstd=dstd,
    center_atomic_numbers=center_atomic_numbers,
    nbr_atomic_numbers=nbr_atomic_numbers,
    max_num_nbrs=max_num_nbrs,
    scaling_matrix=scaling_matrix
)


e_tot, e_atoms, f_atoms, virial = dp_infer.infer(structure=new_structure)
print( "S 2.1. e_tot = {0} eV".format(e_tot.item()) )
print( "S 2.2. e_atoms.shape = ", e_atoms.shape )
print( "S 2.3. f_atoms.shape = ", f_atoms.shape )
print( "S 2.4. virial = \n", virial )      