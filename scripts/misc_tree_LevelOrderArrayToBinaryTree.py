#! /usr/bin/python

"""
Source: https://leetcode.com/problems/recover-binary-search-tree/solutions/32539/Tree-Deserializer-and-Visualizer-for-Python/


"""
class TreeNode:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
    def __repr__(self):
        return 'TreeNode({})'.format(self.val)
    
def deserialize(string):
    if string == '{}':
        return None
    nodes = [None if val == 'null' else TreeNode(int(val))
             for val in string.strip('[]{}').split(',')]
    print ("nodes", nodes)
    print("---")
    kids = nodes[::-1]
    print("kids", kids)
    print("---")
    root = kids.pop()
    for node in nodes:
        print("node", node)
        if node:
            if kids: 
                tmp = kids.pop()
                print("left", tmp)
                node.left  = tmp
            if kids: 
                tmp = kids.pop()
                print("right", tmp)
                node.right = tmp
        print("---")
    return root

def drawtree(root):
    def height(root):
        return 1 + max(height(root.left), height(root.right)) if root else -1
    def jumpto(x, y):
        t.penup()
        t.goto(x, y)
        t.pendown()
    def draw(node, x, y, dx):
        if node:
            t.goto(x, y)
            jumpto(x, y-20)
            t.write(node.val, align='center', font=('Arial', 12, 'normal'))
            draw(node.left, x-dx, y-60, dx/2)
            jumpto(x, y-20)
            draw(node.right, x+dx, y-60, dx/2)
    import turtle
    t = turtle.Turtle()
    t.speed(0); turtle.delay(0)
    h = height(root)
    jumpto(0, 30*h)
    draw(root, 0, 30*h, 40*h)
    t.hideturtle()
    turtle.mainloop()
    
if __name__ == '__main__':
    deserialize('[1,2,3,null,null,4,null,null,5]')

    # drawtree(deserialize('[1,2,3,null,null,4,null,null,5]'))
    # drawtree(deserialize('[2,1,3,0,7,9,1,2,null,1,0,null,null,8,8,null,null,null,null,7]'))
