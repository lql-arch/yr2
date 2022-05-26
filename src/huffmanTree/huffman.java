package huffmanTree;

import java.io.Serializable;

public class huffman implements Comparable<huffman>, Serializable {
    private int weight;
    private Byte data;
    private huffman topLeft;
    private huffman topRight;
    private huffman father;


    public huffman() {
        this.weight = 0;
        this.data = 0;
        this.topLeft = null;
        this.topRight = null;
        this.father = null;
    }

    public huffman(Byte data, int weight) {
        this.weight = weight;
        this.data = data;
        this.topLeft = null;
        this.topRight = null;
        this.father = null;
    }

    public huffman(int weight, Byte data, huffman topLeft, huffman topRight, huffman father) {
        this.weight = weight;
        this.data = data;
        this.topLeft = topLeft;
        this.topRight = topRight;
        this.father = father;
    }

    public void setHuffman(huffman topLeft, huffman topRight) {
        this.topLeft = topLeft;
        this.topRight = topRight;
    }

    public void setFather(huffman father) {
        this.father = father;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public void setStr(Byte data) {
        this.data = data;
    }

    public huffman getTopLeft() {
        return topLeft;
    }

    public huffman getTopRight() {
        return topRight;
    }

    public huffman getFather() {
        return father;
    }

    public int getWeight() {
        return weight;
    }

    public Byte getData() {
        return data;
    }

    @Override
    public int compareTo(huffman o) {
        return this.weight - o.weight;
    }


}