package algs4;

import java.util.Iterator;

public class MyStack<Item> implements Iterable<Item> {
    private Item[] items = (Item[]) new Object[1];
    private int size = 0;

    public boolean isEmpty() {
        return size == 0;
    }

    public int getSize() {
        return size;
    }

    private void resize(int max) {
        Item[] tmp = (Item[]) new Object[max];
        for (int i = 0; i < size; ++i) {
            tmp[i] = items[i];
        }
        items = tmp;
    }

    public void push(Item item) {
        if (size == items.length) {
            resize(2 * size);
        }
        items[size++] = item;
    }

    public Item pop() {
        assert size > 0 : "Cannot pop from a empty stack";
        Item item = items[--size];
        items[size] = null;
        // 保持元素的数量不少于最大容量的 1/4
        if (size > 0 && size == items.length / 4) {
            resize(2 * size);
        }
        return item;
    }

    public Item top() {
        assert size > 0;
        return items[size - 1];
    }

    public Iterator<Item> iterator() {
        return new ReverseArrayIterator();
    }

    private class ReverseArrayIterator implements Iterator<Item> {
        private int i = size;

        public boolean hasNext() {
            return i > 0;
        }

        public Item next() {
            return items[--i];
        }

        public void remove() {
            throw new RuntimeException("Don't try to remove stack item except pop()");
        }
    }
}
