import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']

def plot_results(filename, steps_num):
    with open(filename, 'r') as file:
        lines = file.readlines()

    iterations = []
    current_state = []
    best_state = []

    for line in lines:
        if line.startswith('迭代次数：'):
            iterations.append(int(line.split('：')[1].strip()))
        elif line.startswith('当前解：'):
            current_state.append(int(line.split('：')[1].strip()))
        elif line.startswith('最优解：'):
            best_state.append(int(line.split('：')[1].strip()))

    plt.figure(figsize=(10, 6))
    plt.plot(iterations, current_state, marker='o', label='当前解')
    plt.plot(iterations, best_state, marker='s', label='最优解')
    plt.title('禁忌搜索过程折线图（禁忌长度：'+str(steps_num)+'）')
    plt.xlabel('迭代次数')
    plt.ylabel('值')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{filename[:-4]}.png')
    plt.show()

plot_results('result_steps_5.txt', 5)
plot_results('result_steps_10.txt', 10)
plot_results('result_steps_20.txt', 20)
plot_results('result_steps_30.txt', 30)
plot_results('result_steps_40.txt', 40)
