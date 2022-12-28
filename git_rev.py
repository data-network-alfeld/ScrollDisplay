import subprocess
version = subprocess.run(['git', 'describe', '--tags'], stdout=subprocess.PIPE).stdout.decode('utf-8').strip()
print(f"-DPIO_SRC_TAG=\\\"{version}\\\"")

