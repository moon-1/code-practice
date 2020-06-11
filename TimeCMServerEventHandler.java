import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SocketChannel;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;

import kr.ac.konkuk.ccslab.cm.entity.CMUser;
import kr.ac.konkuk.ccslab.cm.event.CMDummyEvent;
import kr.ac.konkuk.ccslab.cm.event.CMEvent;
import kr.ac.konkuk.ccslab.cm.event.CMFileEvent;
import kr.ac.konkuk.ccslab.cm.event.CMSNSEvent;
import kr.ac.konkuk.ccslab.cm.event.CMSessionEvent;
import kr.ac.konkuk.ccslab.cm.event.CMUserEvent;
import kr.ac.konkuk.ccslab.cm.event.CMUserEventField;
import kr.ac.konkuk.ccslab.cm.event.handler.CMAppEventHandler;
import kr.ac.konkuk.ccslab.cm.info.CMConfigurationInfo;
import kr.ac.konkuk.ccslab.cm.info.CMFileTransferInfo;
import kr.ac.konkuk.ccslab.cm.info.CMInfo;
import kr.ac.konkuk.ccslab.cm.info.CMInteractionInfo;
import kr.ac.konkuk.ccslab.cm.manager.CMDBManager;
import kr.ac.konkuk.ccslab.cm.manager.CMFileTransferManager;
import kr.ac.konkuk.ccslab.cm.stub.CMServerStub;

public class TimeCMServerEventHandler implements CMAppEventHandler {

   private CMServerStub m_serverStub; 
   private TimeCMServer m_server; 

   public TimeCMServerEventHandler(CMServerStub serverStub, TimeCMServer server)  
   {   
      m_serverStub = serverStub;  
      m_server = server;
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

   private void processSessionEvent(CMEvent cme)  
   {   
      

      CMConfigurationInfo confInfo = m_serverStub.getCMInfo().getConfigurationInfo();
      
      CMSessionEvent se = (CMSessionEvent) cme;   
      switch(se.getID())   
      {   case CMSessionEvent.LOGIN:

         printMessage("["+se.getUserName()+"] requests login.\n");
         if(confInfo.isLoginScheme())
         {
            
            boolean ret = CMDBManager.authenticateUser(se.getUserName(), se.getPassword(), 
                  m_serverStub.getCMInfo());
            if(!ret)
            {
               printMessage("["+se.getUserName()+"] authentication fails!\n");
               m_serverStub.replyEvent(cme, 0);
            }
            else
            {
               printMessage("["+se.getUserName()+"] authentication succeeded.\n");
               m_serverStub.replyEvent(cme, 1);
               
               CMUserEvent ue = new CMUserEvent();
               int num = 1;
               String title = "test string";
               System.out.println("====================== test CMUserEvent");
               ue.setStringID("testID");
               ue.setEventField(CMInfo.CM_INT, "intField", String.valueOf(num));
               ue.setEventField(CMInfo.CM_STR, "strField", title);
               m_serverStub.send(ue,se.getUserName());
            }
         }
         break;
      case CMSessionEvent.LOGOUT:

         printMessage("["+se.getUserName()+"] logs out.\n");
         break;
     
      default:
         break;
      }  
   }
   
   private void processDummyEvent(CMEvent cme)
   {
	   Calendar cal = Calendar.getInstance();
	   CMDummyEvent due = (CMDummyEvent) cme;
	   
	   CMInteractionInfo interInfo = m_serverStub.getCMInfo().getInteractionInfo();
       CMUser myself = interInfo.getMyself();
       printMessage("\n클라이언트가 보낸 메세지는 "+ due.getDummyInfo()+" 입니다");
       printMessage("\n클라이언트"+due.getDummyInfo()+"가 시간정보를 요청합니다\n");
       SimpleDateFormat sdf = new SimpleDateFormat("yyyy / MM / dd / HH:mm:ss");
   		String datestr = sdf.format(cal.getTime());
			
		CMDummyEvent replyDue = new CMDummyEvent();
		replyDue.setDummyInfo(datestr);
			       
		if(	false == m_serverStub.send(replyDue,due.getDummyInfo()))
		{
		    printMessage("send error!\n");
		}
		printMessage("\n클라이언트에게 보낸 메세지 :" + datestr);
		printMessage("\n================================================");
		replyDue = null;
		
	   return;
   }
 
   
   private void printMessage(String strText)
   {
      m_server.printMessage(strText);
   }
}