from sklearn.datasets import load_iris
from sklearn.tree import DecisionTreeClassifier, plot_tree, export_text
import matplotlib.pyplot as plt

# Load the iris dataset
iris = load_iris()
X, y = iris.data, iris.target

# Create and fit the model
model = DecisionTreeClassifier(random_state=0)
model.fit(X, y)

# Export the decision tree rules to a text file
tree_rules = export_text(model, feature_names=iris['feature_names'])
with open("decision_tree_rules.txt", "w") as f:
    f.write(tree_rules)

# Plot the tree
plt.figure(figsize=(20,10))
plot_tree(model, filled=True, feature_names=iris.feature_names, class_names=iris.target_names)
plt.show()

print("The decision tree rules have been written to decision_tree_rules.txt")