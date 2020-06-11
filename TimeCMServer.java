import java.awt.BorderLayout;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.text.BadLocationException;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyleContext;
import javax.swing.text.StyledDocument;

import kr.ac.konkuk.ccslab.cm.manager.CMCommManager;
import kr.ac.konkuk.ccslab.cm.stub.CMServerStub;

public class TimeCMServer extends JFrame  {

   
   private static final long serialVersionUID = 1L;
   
   
   private CMServerStub m_serverStub;
   private TimeCMServerEventHandler m_eventHandler;
   private JTextPane m_outTextPane;
   private JTextField m_inTextField;
   

   TimeCMServer()
   {
      
      setTitle("TimeServer");
      setSize(500, 500);
      
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      
      m_serverStub = new CMServerStub();   
      m_eventHandler = new TimeCMServerEventHandler(m_serverStub ,this);  
      

      m_outTextPane = new JTextPane();
      m_outTextPane.setEditable(false);

      StyledDocument doc = m_outTextPane.getStyledDocument();
      addStylesToDocument(doc);
      
      add(m_outTextPane, BorderLayout.CENTER);
      JScrollPane scroll = new JScrollPane (m_outTextPane, 
               JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
      
      add(scroll);
      
      m_inTextField = new JTextField();
      add(m_inTextField, BorderLayout.SOUTH);
      
      m_serverStub = new CMServerStub();
      m_eventHandler = new TimeCMServerEventHandler(m_serverStub,this);
   
      setVisible(true);
      startCM();
       
      
   
   }   
   
   public CMServerStub getServerStub()  
   {   
      return m_serverStub;  
   }    
   
   public TimeCMServerEventHandler getServerEventHandler()  
   {   
      return m_eventHandler;  
   } 
   
   public void startCM()
   {
      boolean bRet = false;
      
      String strSavedServerAddress = null;
      String strCurServerAddress = null;
      int nSavedServerPort = -1;
      
      strSavedServerAddress = m_serverStub.getServerAddress();
      strCurServerAddress = CMCommManager.getLocalIP();     
      nSavedServerPort = m_serverStub.getServerPort();
      JTextField serverAddressTextField = new JTextField(strCurServerAddress);
      JTextField serverPortTextField = new JTextField(String.valueOf(nSavedServerPort));
      Object msg[] = {
            "Server Address: ", serverAddressTextField,
            "Server Port: ", serverPortTextField
      };
      int option = JOptionPane.showConfirmDialog(null, msg, "Server Information", JOptionPane.OK_CANCEL_OPTION);

// update the server info if the user would like to do
      if (option == JOptionPane.OK_OPTION) 
      {
         String strNewServerAddress = serverAddressTextField.getText();
         int nNewServerPort = Integer.parseInt(serverPortTextField.getText());
         if(!strNewServerAddress.equals(strSavedServerAddress) || nNewServerPort != nSavedServerPort)
            m_serverStub.setServerInfo(strNewServerAddress, nNewServerPort);
      }
      bRet = m_serverStub.startCM();
      if(!bRet)
      {
         printStyledMessage("CM initialization error!\n", "bold");
      }
      else
      {
         printStyledMessage("\nServer TimeCM starts.\n", "bold");
         printMessage("\n시간을 알려주는 서버입니다.\n");                           
      }

      m_inTextField.requestFocus();

   }
   
   
   public void printMessage(String strText)
   {
      StyledDocument doc = m_outTextPane.getStyledDocument();
      try {
         doc.insertString(doc.getLength(), strText, null);
         m_outTextPane.setCaretPosition(m_outTextPane.getDocument().getLength());

      } catch (BadLocationException e) {
         // TODO Auto-generated catch block
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
         // TODO Auto-generated catch block
         e.printStackTrace();
      }
      
      return;
   }
      
   private void addStylesToDocument(StyledDocument doc)
   {
      Style defStyle = StyleContext.getDefaultStyleContext().getStyle(StyleContext.DEFAULT_STYLE);

      Style regularStyle = doc.addStyle("regular", defStyle);
      StyleConstants.setFontFamily(regularStyle, "SansSerif");
      
      Style boldStyle = doc.addStyle("bold", defStyle);
      StyleConstants.setBold(boldStyle, true);
   }
   
    public static void main(String[] args) 
    {   
       TimeCMServer server = new TimeCMServer();   
       CMServerStub cmStub = server.getServerStub();   
       cmStub.setAppEventHandler(server.getServerEventHandler());     
   } 
}