import java.util.*;

/**
 *
 * @author Stephen A. Adubi
 * @modified Apr. 29, 2023
 */

class Node //the Node class
{
    public int data; //data of the node
    public Node left; //left child of the node -- A node itself
    public Node right; //right child of the node -- A node itself
}

class BinarySearchTree {
    Node root;
    int direction; //indicates the position of a child node; 0 = left, 1 = right, -1 = no parent
    public BinarySearchTree() { root = null; } //constructor
    public void insert(int key) //publicly accessible version
    {
        if(isEmpty()) //insert data as the root node if tree is empty
        {
            Node temp = new Node();
            temp.data = key;
            temp.left = null;
            temp.right = null;
            root = temp;
            System.out.print(key + " added to the tree\n");
        }

        else
            insert(root, key); //otherwise traverse down the tree until you find a suitable spot
    }

    void insert(Node curNode, int key) //automatically called via the else part of the above method
    {
        if(key < curNode.data)
        {
            if(curNode.left==null) /* if the current node has no left child then
                                    insert the item as the left child */
            {
                Node temp = new Node(); //create a new node
                temp.data = key; //set it's data
                temp.left = null; //it has no left child yet
                temp.right = null; //it has no right child yet
                curNode.left = temp; //make it the left child of the current node
                System.out.print(key + " added to the tree\n");
            }

            else
                insert(curNode.left, key); /*otherwise try to insert the data into the left
                                            subtree of the current node*/
        }

        else
        {
            if(curNode.right == null)
            {
                Node temp = new Node();
                temp.data = key;
                temp.left = null;
                temp.right = null;
                curNode.right = temp;
                System.out.print(key + " added to the tree\n");
            }

            else
                insert(curNode.right, key);
        }
    }

    public boolean isEmpty(){ return root == null; }

    public void levelOrder(){
        if(root == null)
            System.out.print("No data in the tree\n");
        else{
            System.out.print("Level order display below...\n");
            levelOrder(root);
            System.out.println();
        }
    }

    public void preOrder(){
        if(root == null)
            System.out.print("No data in the tree\n");
        else{
            System.out.print("Pre order display below...\n");
            preOrder(root);
            System.out.println();
        }
    }

    public void postOrder(){
        if(root == null)
            System.out.print("No data in the tree\n");
        else{
            System.out.print("Post order display below...\n");
            postOrder(root);
            System.out.println();
        }
    }

    public void inOrder(){
        if(root == null)
            System.out.print("No data in the tree\n");
        else{
            System.out.print("In order display below...\n");
            inOrder(root);
            System.out.println();
        }
    }

    /**
     * Implements level order traversal
     * A queue is used. Details as follows:
     * 1. Push the root as the first element of the queue <br/> 2. Loop (While queue isn't empty) <br/>
     * 3. Retrieve and Delete the Node at the front of the queue <br/> 4. Print its data <br/>
     * 5. If the retrieved node has a left child, enqueue the left child
     * 6. If the retrieved node has a right child, enqueue the right child
     * 7. Goto Step 2
     * @param theNode the node at the root of the tree
     */
    private void levelOrder(Node theNode){
        Queue<Node> queue = new LinkedList<>();
        if(root != null) queue.add(theNode); //Step 1
        while(!queue.isEmpty()){ //Step 2
            Node temp = queue.remove(); // retrieve item (the node) at the front of the queue and delete it.. // Step 3
            System.out.print(temp.data + " "); //Step 4
            if(temp.left != null) queue.add(temp.left); //Step 5
            if(temp.right != null) queue.add(temp.right); //Step 6
        }
    }

    private void preOrder(Node theNode){
        if(theNode != null){
            System.out.print(theNode.data + " ");
            preOrder(theNode.left);
            preOrder(theNode.right);
        }
    }

    private void inOrder(Node theNode) {
        if (theNode != null) {
            inOrder(theNode.left);
            System.out.print(theNode.data + " ");
            inOrder(theNode.right);
        }
    }

    private void postOrder(Node theNode) {
        if (theNode != null) {
            postOrder(theNode.left);
            postOrder(theNode.right);
            System.out.print(theNode.data + " ");
        }
    }

    private Node[] search(int key){ //returns the parent node and the found node
        Node temp = root;
        Node parent = null;
        direction = -1;
        while (temp != null) {
            if (temp.data == key)
                return new Node[] {parent, temp};
            else if (key < temp.data) {
                parent = temp;
                temp = temp.left;
                direction = 0;
            }
            else {
                parent = temp;
                temp = temp.right;
                direction = 1;
            }
        }

        return new Node[] {};
    }

    private Node search(Node parent, Node replacement){ //returns the parent of (replacement) node
        Node temp = null;
        while (parent != replacement){
            temp = parent;
            if(replacement.data < parent.data)
                parent = parent.left;
            else
                parent = parent.right;
        }

        return temp;
    }

    public void delete(int key){
        if(isEmpty()) {
            System.out.printf("The BST is currently empty, nothing to delete\n", key);
            return;
        }

        Node[] parent_child_arr = search(key);
        if(parent_child_arr.length == 0)
            System.out.printf("Key (%d) to be deleted is not in the tree\n", key);
        else{
            Node deletedNode = delete(parent_child_arr);
            System.out.printf("Node with key: %d deleted from the BST\n", deletedNode.data);
        }
    }

    private Node delete(Node[] parent_child_arr) {
        Node parent =  parent_child_arr[0]; // retrieve the parent node
        Node theNode = parent_child_arr[1]; // retrieve the child node
        if(theNode.left == null && theNode.right == null) { // the node has no child (i.e., a leaf)
            if(direction == 0)
                parent.left = null;
            else
                parent.right = null;
        }
        else{ // if we have a non-simple case, i.e., the node to be deleted has at least one child
            Node replacementNode = null;
            if(theNode.left != null) { //give priority to the left sub-tree, find a successor from here
                replacementNode = findMaxInLeftSubTree(theNode.left);
                replacementNode.right = theNode.right;
                if(replacementNode != theNode.left) {
                    Node parent_of_replacement = search(theNode.left, replacementNode);
                    parent_of_replacement.right = replacementNode.left;
                    replacementNode.left = theNode.left;
                }
            }
            else {
                replacementNode = findMinInRightSubTree(theNode.right);
                if(replacementNode != theNode.right) {
                    Node parent_of_replacement = search(theNode.right, replacementNode);
                    parent_of_replacement.left = replacementNode.right;
                    replacementNode.right = theNode.right;
                }
            }

            if(direction == -1)
                root = replacementNode;
            else if(direction == 0)
                parent.left = replacementNode;
            else
                parent.right = replacementNode;
        }

        return theNode;
    }

    private Node findMaxInLeftSubTree(Node successor){
        while(successor.right != null)
            successor = successor.right;
        return successor;
    }

    private Node findMinInRightSubTree(Node successor){
        while(successor.left != null)
            successor = successor.left;
        return successor;
    }

    public static void main(String[] args) {
        BinarySearchTree bst = new BinarySearchTree();
        //Insertion test data: 53, 72, 30, 61, 39, 14, 84, 79, 47, 9
        bst.insert(90);
        bst.insert(81);
        bst.insert(79);
        bst.insert(83);
        bst.insert(85);

        bst.levelOrder();
        bst.delete(84); bst.levelOrder();
        bst.delete(85); bst.levelOrder();
        bst.insert(82); bst.levelOrder();
        bst.delete(90); bst.levelOrder(); bst.inOrder();
    }
}
