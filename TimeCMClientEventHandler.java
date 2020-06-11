import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;

import javax.swing.JTextPane;
import javax.swing.text.BadLocationException;
import javax.swing.text.StyledDocument;

import kr.ac.konkuk.ccslab.cm.event.CMDummyEvent;
import kr.ac.konkuk.ccslab.cm.event.CMEvent;
import kr.ac.konkuk.ccslab.cm.event.CMSNSEvent;
import kr.ac.konkuk.ccslab.cm.event.CMSessionEvent;
import kr.ac.konkuk.ccslab.cm.event.handler.CMAppEventHandler;
import kr.ac.konkuk.ccslab.cm.info.CMConfigurationInfo;
import kr.ac.konkuk.ccslab.cm.info.CMInfo;
import kr.ac.konkuk.ccslab.cm.info.CMInteractionInfo;
import kr.ac.konkuk.ccslab.cm.info.CMSNSInfo;
import kr.ac.konkuk.ccslab.cm.sns.CMSNSContent;
import kr.ac.konkuk.ccslab.cm.sns.CMSNSContentList;
import kr.ac.konkuk.ccslab.cm.stub.CMClientStub;
import kr.ac.konkuk.ccslab.cm.util.CMUtil;

public class TimeCMClientEventHandler implements CMAppEventHandler {
   
    private long m_lStartTime;
   private TimeCMClient m_client;
   private CMClientStub m_clientStub;
 
   private PrintWriter m_pw;      

   int m_nSimNum ;
   public TimeCMClientEventHandler(CMClientStub clientStub, TimeCMClient client)
   {
      m_client = client;
      m_clientStub = clientStub;
      m_nSimNum = 0;
      m_pw = null;
      
   }
   public void setStartTime(long time)
   {
      m_lStartTime = time;
   }
   
   public long getStartTime()
   {
      return m_lStartTime;
   }
   
    public void printMessage(String strText)
      {
       m_client.printMessage(strText);
         
         return;
      }
    
   @Override   
   public void processEvent(CMEvent cme) {
      switch(cme.getType())  
      {
      case CMInfo.CM_SESSION_EVENT:   
         processSessionEvent(cme);   
         break;
      case CMInfo.CM_DUMMY_EVENT:
    	  processDummyEvent(cme);
    	  break;
    	 
      default:
         return;
      }
   }
   
   private void processDummyEvent(CMEvent cme)
   {
	   CMDummyEvent replyDue = (CMDummyEvent) cme;
	   printMessage("\n서버가 보낸 메세지 (현재 시간) :  "+replyDue.getDummyInfo());
   }
 
   private void processSessionEvent(CMEvent cme)
   {
      CMSessionEvent se = (CMSessionEvent)cme;
      switch(se.getID())
      {
      case CMSessionEvent.LOGIN_ACK:
         if(se.isValidUser() == 0)
         {
            printMessage("This client fails authentication by the default server!\n");
            
         }
         else if(se.isValidUser() == -1)
         {
            printMessage("This client is already in the login-user list!\n");
         }
         else
         {
            printMessage("This client successfully logs in to the default server.\n");
            CMInteractionInfo interInfo = m_clientStub.getCMInfo().getInteractionInfo();
            
            m_client.setTitle("CM Client ["+interInfo.getMyself().getName()+"]");
         }
         break;
      }
   }

}