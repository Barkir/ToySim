import matplotlib.pyplot as plt # build diagram
import os # work with directories
from datetime import datetime

HYPERFINE_PATH="./hyperfine"
IMAGES_PATH = "./images"

files = [os.path.join(HYPERFINE_PATH, k) for k in os.listdir(HYPERFINE_PATH)]

plt.style.use("seaborn-v0_8")

times = []
for file in files:
    file2str = open(file).readlines()
    times.append(float(file2str[1].split(":")[1].split("ms")[0]))

nums = [k+1 for k in range(len(times))]
times = sorted(times)
print(times)

diagram=plt.bar(nums, times)

plt.xticks(rotation=45, ha='right')

plt.xlim(0, 8)
plt.ylim(0, 200)

plt.grid(axis='y', alpha=0.3)

plt.xlabel("Benchmark number")
plt.ylabel("Time, ms")


timestamp = datetime.now().strftime("%Y%m%d_%H%M%S_%f")


img_name = f"{IMAGES_PATH}/chart_{timestamp}"
plt.savefig(img_name, dpi=300, bbox_inches='tight',
            facecolor='white', edgecolor='none')

plt.tight_layout()
plt.close()
