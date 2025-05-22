import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math

#Dosyayı oku
df = pd.read_csv("sonuclar.txt")

# Ortalama c hesapla
c_merge_avg = df['c_merge'].mean()
c_quick_avg = df['c_quick'].mean()

# Teorik süreleri hesapla
df['merge_theoretical'] = df['n'] * np.log2(df['n']) * c_merge_avg
df['quick_theoretical'] = df['n'] * np.log2(df['n']) * c_quick_avg

# 🎨 T(n) vs c·n·logn grafiği
plt.figure(figsize=(10, 5))
plt.plot(df['n'], df['merge_time'], 'o-', label='MergeSort T(n)')
plt.plot(df['n'], df['merge_theoretical'], '--', label='MergeSort Teorik')

plt.plot(df['n'], df['quick_time'], 'o-', label='QuickSort T(n)')
plt.plot(df['n'], df['quick_theoretical'], '--', label='QuickSort Teorik')

plt.xlabel('n')
plt.ylabel('Zaman (saniye)')
plt.title('T(n) ve c·n·log₂(n) Karşılaştırması')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("zaman_karsilastirma.png")
plt.show()

# 📉 c değerleri grafiği
plt.figure(figsize=(10, 5))
plt.plot(df['n'], df['c_merge'], 'o-', label='c (MergeSort)')
plt.plot(df['n'], df['c_quick'], 'o-', label='c (QuickSort)')

plt.xlabel('n')
plt.ylabel('c değeri')
plt.title('Her n için c katsayısı')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("c_katsayilari.png")
plt.show()


table_data = df[["n", "c_merge", "c_quick"]]
fig, ax = plt.subplots(figsize=(6, 2))
ax.axis('off')  # Eksenleri kapat

# Tabloyu oluştur
table = ax.table(
    cellText=table_data.values,
    colLabels=table_data.columns,
    loc='center'
)
table.auto_set_font_size(False)
table.set_fontsize(10)
table.scale(1, 2)  # Hücre boyutunu ayarla
plt.title("c Katsayıları Tablosu", pad=20)
plt.tight_layout()
plt.savefig("c_katsayilari_tablosu.png")
plt.show()
