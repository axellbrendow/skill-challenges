/*
Commands to compile and run:

javac InteractiveGUI.java
java InteractiveGUI

*/

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class InteractiveGUI
{
    static class Board extends JPanel
    {
        public static int squareLine = 0;
        public static int squareColumn = 0;
        public static int NUM_LINES = 10;
        public static int NUM_COLUMNS = 10;
        public static Color BG_COLOR = new Color(0x4b4b4b); // gray
        public static Color SQUARE_COLOR = new Color(0xfff200); // yellow

        public Board()
        {
            setFocusable(true); // To listen to key events
            requestFocusInWindow(); // Autofocus

            addKeyListener(new KeyAdapter()
            {
                @Override
                public void keyPressed(KeyEvent e)
                {
                    move(e.getKeyCode());
                }
            });
        }

        @Override
        public void paint(Graphics g)
        {
            super.paint(g);

            g.setColor(BG_COLOR);
            g.fillRect(0, 0, getWidth(), getHeight());

            g.setColor(SQUARE_COLOR);
            drawSquare(squareLine, squareColumn, g);

            g.setColor(new Color(0xff4d4d)); // red
            ((Graphics2D) g).setStroke(new BasicStroke(5));
            ((Graphics2D) g).setRenderingHint(
                RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            drawX(squareLine, squareColumn, g);
        }

        public int getColumnSize()
        {
            return getWidth() / NUM_COLUMNS;
        }

        public int getLineSize()
        {
            return getHeight() / NUM_LINES;
        }

        public void drawSquare(int line, int column, Graphics g)
        {
            int columnSize = getColumnSize();
            int lineSize = getLineSize();
            int startX = column * columnSize;
            int startY = line * lineSize;

            g.fillRect(startX, startY, columnSize,  lineSize);
        }

        public void drawX(int line, int column, Graphics g)
        {
            int columnSize = getColumnSize();
            int lineSize = getLineSize();
            int startX = column * columnSize;
            int startY = line * lineSize;

            g.drawLine(startX, startY, startX + columnSize,  startY + lineSize);
            g.drawLine(startX, startY + lineSize, startX + columnSize,  startY);
        }

        public void move(int key)
        {
            if (key == KeyEvent.VK_UP || key == KeyEvent.VK_RIGHT ||
                key == KeyEvent.VK_DOWN || key == KeyEvent.VK_LEFT)
            {
                switch (key)
                {
                    case KeyEvent.VK_UP:
                        if (squareLine > 0) squareLine--;
                        break;

                    case KeyEvent.VK_RIGHT:
                        if (squareColumn < NUM_COLUMNS - 1) squareColumn++;
                        break;

                    case KeyEvent.VK_DOWN:
                        if (squareLine < NUM_LINES - 1) squareLine++;
                        break;

                    case KeyEvent.VK_LEFT:
                        if (squareColumn > 0) squareColumn--;
                        break;
                }

                repaint();
            }
        }
    }

    public static final int WINDOW_WIDTH = 700;
    public static final int WINDOW_HEIGHT = 700;

    public static void main(String[] args)
    {
        JFrame jFrame = new JFrame("Press Up/Down/Right/Left to move!");
        jFrame.setBounds(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        Container pane = jFrame.getContentPane();

        pane.add(new Board());

        jFrame.setVisible(true);
    }
}
