import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.text.BadLocationException;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyleContext;
import javax.swing.text.StyledDocument;

import kr.ac.konkuk.ccslab.cm.entity.CMMember;
import kr.ac.konkuk.ccslab.cm.entity.CMUser;
import kr.ac.konkuk.ccslab.cm.event.CMDummyEvent;
import kr.ac.konkuk.ccslab.cm.info.CMConfigurationInfo;
import kr.ac.konkuk.ccslab.cm.info.CMInfo;
import kr.ac.konkuk.ccslab.cm.info.CMInteractionInfo;
import kr.ac.konkuk.ccslab.cm.stub.CMClientStub;

public class TimeCMClient extends JFrame{
	private JTextPane m_outTextPane;
    private JTextField m_inTextField;

    private JButton loginButton;
    private JButton timeButton;

    CMClientStub m_clientStub; 
    TimeCMClientEventHandler m_eventHandler;
    
    public TimeCMClient() { 
       
       
       MyActionListener cmActionListener = new MyActionListener();
       setTitle("Time Client");
       setSize(500,500);
       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       
       m_outTextPane = new JTextPane();
       StyledDocument doc = m_outTextPane.getStyledDocument();
         addStylesToDocument(doc);
         add(m_outTextPane, BorderLayout.CENTER);
         JScrollPane centerScroll = new JScrollPane (m_outTextPane, 
                  JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

         getContentPane().add(centerScroll, BorderLayout.CENTER);
         
         m_inTextField = new JTextField();
         add(m_inTextField, BorderLayout.SOUTH);

       JPanel topButtonPanel = new JPanel();
       topButtonPanel.setBackground(new Color(220,220,220));
       topButtonPanel.setLayout(new FlowLayout());
       add(topButtonPanel, BorderLayout.NORTH);
         
       loginButton = new JButton("login");
       loginButton.addActionListener(cmActionListener);
       topButtonPanel.add(loginButton);
       
       timeButton = new JButton("time");
       timeButton.addActionListener(cmActionListener);
       topButtonPanel.add(timeButton);

       setVisible(true);
       m_clientStub = new CMClientStub();
       m_eventHandler = new TimeCMClientEventHandler(m_clientStub, this);
    }
   
    private void addStylesToDocument(StyledDocument doc)
      {
         Style defStyle = StyleContext.getDefaultStyleContext().getStyle(StyleContext.DEFAULT_STYLE);

         Style regularStyle = doc.addStyle("regular", defStyle);
         StyleConstants.setFontFamily(regularStyle, "SansSerif");
         
         Style boldStyle = doc.addStyle("bold", defStyle);
         StyleConstants.setBold(boldStyle, true);
         
         Style linkStyle = doc.addStyle("link", defStyle);
         StyleConstants.setForeground(linkStyle, Color.BLUE);
         StyleConstants.setUnderline(linkStyle, true);
      }
    
    public void printMessage(String strText)
      {
         StyledDocument doc = m_outTextPane.getStyledDocument();
         try {
            doc.insertString(doc.getLength(), strText, null);
            m_outTextPane.setCaretPosition(m_outTextPane.getDocument().getLength());

         } catch (BadLocationException e) {
            e.printStackTrace();
         }
         
         return;
      }
    
    public void printStyledMessage(String strText, String strStyleName)
      {
         StyledDocument doc = m_outTextPane.getStyledDocument();
         try {
            doc.insertString(doc.getLength(), strText, doc.getStyle(strStyleName));
            m_outTextPane.setCaretPosition(m_outTextPane.getDocument().getLength());

         } catch (BadLocationException e) {
            e.printStackTrace();
         }
         
         return;
      }
    
    public void testLoginDS()
      {
         String strUserName = null;
         String strPassword = null;
         boolean bRequestResult = false;

         printMessage("====== login to default server\n");
         JTextField userNameField = new JTextField();
         JPasswordField passwordField = new JPasswordField();
         Object[] message = {
               "User Name:", userNameField,
               "Password:", passwordField
         };
         int option = JOptionPane.showConfirmDialog(null, message, "Login Input", JOptionPane.OK_CANCEL_OPTION);
         if (option == JOptionPane.OK_OPTION)
         {
            strUserName = userNameField.getText();
            strPassword = new String(passwordField.getPassword()); 
            
            m_eventHandler.setStartTime(System.currentTimeMillis());
            bRequestResult = m_clientStub.loginCM(strUserName, strPassword);
            
            if(bRequestResult)
            {
               printMessage("successfully sent the login request.\n");
               
            }
            else
            {
               printStyledMessage("failed the login request!\n", "bold");
            }
         }
         
         printMessage("======\n");
      }
    
    public void requestTime()
    {
  	 
       CMInteractionInfo interInfo = m_clientStub.getCMInfo().getInteractionInfo();
       CMUser myself = interInfo.getMyself();
          
       String strInput = myself.getName().trim();
          		
          CMDummyEvent due = new CMDummyEvent();
          due.setDummyInfo(strInput);
          m_clientStub.send(due,"SERVER");
          printMessage("\n서버로 전송한 메세지는 : "+strInput+" 입니다");
          printMessage("\n================================================");
          due = null;

       return;
    }
    
    public class MyActionListener implements ActionListener {
         public void actionPerformed(ActionEvent e)
         {
            JButton button = (JButton) e.getSource();
            if(button.getText().equals("login"))
            {
               testLoginDS();
               
            }
            else if(button.getText().equals("time"))
            {
               requestTime();
            }
            
         }
    }

    public static void main(String[] args)
      {
       TimeCMClient client = new TimeCMClient(); 
         client.m_clientStub.setAppEventHandler(client.m_eventHandler);
         client.m_clientStub.startCM();
      }
}