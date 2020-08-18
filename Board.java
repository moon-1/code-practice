import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
improt javax.persistence.Table;

import org.hibernate.annotations.CreationTimestamp;
import org.hibernate.annotations.UpdateTimestamp;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
@Entity
@Table(name="table_boards")
public class Board{
  @Id
  @GeneratedValue(strategy = GenerationType.AUTO) //식별키의 생성 전략 지정 AUTO : 특정 데이터베이스에 맞게 자동으로 생성되는 방식
  private Long bno;
  private String title;
  private String writter;
  private String content;
  
  //org.hibernate 패키지의 어노테이션
  //엔터티가 생성되거나 업데이트되는 시점의 날짜 데이터를 기록하는 설정
  @CreationTimestamp
  private Timestamp regdate;
  @UpdateTimestamp
  private Timestamp updatedate;
  
  
}
