# import os
# import subprocess
# import pandas as pd
# import matplotlib.pyplot as plt

# vaccination_rates = [round(i * 0.1, 1) for i in range(11)]
# steps = []

# for rate in vaccination_rates:
#     print(f"Running with vaccination rate = {rate}")

#     # نعدّل الملف يدوياً
#     with open("../configExample/disease_in.ini", "r") as f:
#         lines = f.readlines()

#     with open("../configExample/disease_in.ini", "w") as f:
#         for line in lines:
#             if line.startswith("vaccination_rate"):
#                 f.write(f"vaccination_rate = {rate}\n")
#             else:
#                 f.write(line)

#     # نشغّل المحاكاة
#     subprocess.run(["./main_exec"])

#     # نقرأ عدد الأيام من ملف الـ CSV
#     df = pd.read_csv("../eport_data/disease_stats.csv")
#     val = int(df[df["key"] == "total_steps"]["value"].values[0])
#     steps.append(val)

# # نرسم الجراف
# plt.plot(vaccination_rates, steps, marker="o")
# plt.xlabel("Vaccination Rate")
# plt.ylabel("Days Until Disease Extinction")
# plt.title("Effect of Vaccination Rate on Simulation")
# plt.grid(True)
# plt.savefig("report_data/vaccination_effect.png")
# plt.show()