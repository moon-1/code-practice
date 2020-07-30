package com.example.demo;

import java.util.Date;

import javax.annotation.Resource;

import org.springframework.beans.factory.annotation.Autowired;

public class MemberRegisterService {
	private MemberDao memberDao;

	@Autowired//스프링이 의존 객체를 찾아서 주입해줌
	public MemberRegisterService(MemberDao memberDao) {
		this.memberDao = memberDao;
	}
	
	public MemberRegisterService() {
	}

	public void regist(RegisterRequest req) {
		Member member = memberDao.selectByEmail(req.getEmail());
		if (member != null) {
			throw new AlreadyExistingMemberException("dup email " + req.getEmail());
		}
		Member newMember = new Member(
				req.getEmail(), req.getPassword(), req.getName(),
				new Date());
		memberDao.insert(newMember);
	}
}
