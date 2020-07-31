import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import spring.MemberDao;
import spring.MemberInfoPrinter;
import spring.MemberPrinter;
import spring.MemberRegisterService;

/*자바 설정을 이용한 자동 주입*/
@Configuration
public class JavaConfig{
  
  @Bean
  public MemberDao memberDao(){
    return new MemberDao();
    }
  
  @Bean
  public MemberRegisterService memberRegSvc(){
    return new MemberRegisterService(memberDao());
  }
  
  @Bean
  public MemberPrinter printer(){
    return new MemberPrinter();
  }
  
  @Bean
  public MemberInfoPrinter infoPrinter(){
    MemberInfoPrinter infoPrinter = new MemberInfoPrinter();
    return infoPrinter;
  }
  
}
