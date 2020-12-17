def create_tree_node(value):
    node = {"value": value, "right": None, "left": None}
    return node


class BST:
    def __init__(self):
        self.root = None
        self.current = self.root

    def insert(self, value):
        node = create_tree_node(value)
        if not self.root:
            self.root = node
            return

        current = self.root
        while True:
            if value > current["value"]:
                if not current["right"]:
                    current["right"] = node
                    break
                current = current["right"]
                continue
            elif value < current["value"]:
                if not current["left"]:
                    current["left"] = node
                    break
                current = current["left"]
                continue
        return

    def lookup(self, value):
        current = self.root
        while current != None:
            if value > current["value"]:
                current = current["right"]
            elif value < current["value"]:
                current = current["left"]
            elif value == current["value"]:
                return current
        return False

    def remove(self, current, value):
        if not self.current:
            return None
        elif value < self.current["value"]:
            self.current["left"] = self.remove(self.current["left"], value)
        elif value > current["value"]:
            self.current["right"] = self.remove(self.current["right"], value)
        else:
            # First case: No child
            if not self.current["right"] and not self.current["left"]:
                del self.current
                self.current = None
            # Second case: One child
            elif not self.current["left"]:
                del self.current
                self.current = self.current["right"]
            elif not self.current["right"]:
                del self.current
                self.current = self.current["left"]
            # Third case: Two childs
            else:
                # Finding the smallest node
                tmp = self.current["right"]
                while tmp["left"]:
                    tmp = tmp["left"]
                    continue
                self.current["value"] = tmp["value"]
                self.current["right"] = self.remove(
                    self.current["right"], self.current["value"])
        return self.current


def insert(root, value, prev):
    if not root:
        node = create_tree_node(value)
        if node["value"] > prev["value"]:
            prev["right"] = node
            return
        prev["left"] = node
        return

    if value > root["value"]:
        return insert(root["right"], value, root)
    return insert(root["left"], value, root)

def main():
    tree = BST()
    tree.insert(1)
    insert(tree.root, 3, tree.root)
    insert(tree.root, 4, tree.root)
    insert(tree.root, 5, tree.root)
    insert(tree.root, 8, tree.root)
    tree.remove(tree.root, 3)
    print(tree.lookup(1))


if __name__ == "__main__":
    main()
