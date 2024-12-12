import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = {'Name': ['Alice', 'Bob', 'Charlie', 'David'],
        'Age': [24, 27, 22, 32],
        'Score': [85, 92, 88, 79]}

# Converting the dataset to a DataFrame
df = pd.DataFrame(data)

# Displaying the DataFrame
df

# Plotting a bar chart of Scores
plt.bar(df['Name'], df['Score'], color='skyblue')
plt.xlabel('Name')
plt.ylabel('Score')
plt.title('Scores of Students')
plt.show()

# Calculating the mean age
mean_age = df['Age'].mean()
print(f"The average age is {mean_age}")
