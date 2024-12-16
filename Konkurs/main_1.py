import matplotlib.pyplot as plt
import numpy as np

# Чтение данных из файла
data = np.loadtxt('word_freq.txt')
ranks = data[:, 0]
frequencies = data[:, 1]

# Построение графика
plt.loglog(ranks, frequencies, 'bo', markersize=2)
plt.xlabel('Rank')
plt.ylabel('Frequency')
plt.title('Zipf\'s Law')
plt.grid(True)
plt.show()
