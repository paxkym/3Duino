package com.threeduino;
import com.fazecast.jSerialComm.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Hello world!
 *
 */
public class App 
{
    JFrame frame = new JFrame("3Duino interfacer");
    JPanel panel = new JPanel();
    JPanel topPanel = new JPanel();
    JComboBox portList = new JComboBox();
    DefaultComboBoxModel portListModel = new DefaultComboBoxModel();
    JLabel terminal = new JLabel();

    int frameHeight = 200*2;
    int frameWidth = 322*2;
    String termcont = "";

    public static void main( String[] args ){
        App app = new App();
    }

    void getSerialPorts(){
        pushTerminal("Obtaining new serial ports...");
        SerialPort[] slist = SerialPort.getCommPorts();
        String[] nlist = new String[slist.length];
        portListModel = new DefaultComboBoxModel();
        for(int i = 0;i<slist.length;i++) portListModel.addElement(slist[i].getDescriptivePortName());
        portList.setModel(portListModel);
        pushTerminal("Serial ports obtained");
        return;
    }
    void examinePort(){
    pushTerminal("Testing serial port");
    SerialPort.getCommPorts()[portList.getSelectedIndex()].getDescriptivePortName();
    // Todo: add actual communication with the serial port
    }

    void pushTerminal(String input){
        terminal.setText(input);
    }

    public class Refresher implements ActionListener{
        public void actionPerformed(ActionEvent e){  
            getSerialPorts();
        }  
    }
    public class Tester implements ActionListener{
        public void actionPerformed(ActionEvent e){  
            examinePort();
        }  
    }

    public App(){
        // GUI stuff
        // Main panel
        panel.setLayout(new BorderLayout());
            // Sub panel
            GridLayout topLayout = new GridLayout(1, 3);
            topPanel.setLayout(topLayout);
            JButton updatePortsButton = new JButton("Refresh");
            JButton performTestButton = new JButton("Test port");
            updatePortsButton.addActionListener(new Refresher());
            performTestButton.addActionListener(new Tester());
            topPanel.add(updatePortsButton, 0);
            getSerialPorts();
            topPanel.add(portList, 1);
            
        panel.add(terminal, BorderLayout.CENTER);
        panel.add(topPanel, BorderLayout.PAGE_START);
        frame.add(panel);
        frame.setSize(frameWidth, frameHeight);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        pushTerminal("");
        

        
    }
}
