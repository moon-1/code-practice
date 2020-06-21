#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define COMMAND_LEN 100
#include "Queue.h"

typedef struct Process
{
        int process_ID;
        int arrival;
        int CPU_burst;
        int start;
        int finish;
        int waiting;
        int turn_around;
        int response;
        int NO_context;
        int count;
        int number;
}process;

int  main()
{
	Queue q;
	QueueInit(&q);
	int temp,i,j,total,flag,k,count;
	int num = 0;
	float sumCPU = 0;
        float sumwait = 0;
        float sumturn = 0;
        float sumresponse = 0;
        int sumcontext = 0;
        int pcount = 0;
        int Q=0;
	int scheduler;
	FILE *fp;
        FILE *fp1;
        char tmp;
	char myscheduler[50];
	char input[20];
	char *command[10] = {NULL, };
	int timeQ = 0;
	char *token;
	printf("\nunixprompt> ");
	scanf("%[^\n]s",myscheduler);
	token = strtok(myscheduler," ");
	i=0;
	while(token!=NULL)
	{
		command[i] = token;
		i++;
		token = strtok(NULL," ");
	}
	i=0;
	scheduler = atoi(command[2]);
	if(scheduler==1){
	timeQ = atoi(command[3]);}
	fp  = fopen(command[1],"r");
        fp1 = fopen(command[1],"r");
        while(fscanf(fp1,"%c",&tmp)!=EOF)
        {
                if(tmp=='\n')
                pcount++;
        }
        int seq[pcount];
        process *p =malloc(sizeof(process)*pcount);
        for(i = 0 ; i < pcount ; i++)
        {
                fscanf(fp,"%d %d %d\n",&p[i].process_ID,&p[i].arrival,&p[i].CPU_burst);
                total= total + p[i].CPU_burst;
                p[i].count = p[i].CPU_burst;
                p[i].number = i;
        }
        /*정렬*/
        for(i = 0; i < pcount-1; i++)
        {
                for(j = 0; j < (pcount-i)-1; j++)
                {
                        if(p[j].arrival > p[j+1].arrival)
                        {
                                temp = p[j].number;
                                p[j].number = p[j+1].number;
                                p[j+1].number = temp;
                        }
                }
        }
        for(i = 0; i < pcount ; i++)
        {
                seq[i] = p[i].number;
		p[i].NO_context = 0;
        }
if(scheduler == 1){
	Enqueue(&q,p[seq[num]].process_ID);
	i = p[seq[num]].arrival;
	num++;
	while(i<total)
	{	
			while(QIsEmpty(&q))
			{
				i++;
				total++;
				if(i == p[seq[num]].arrival)
				{ 
					Enqueue(&q,p[seq[num]].process_ID);
					num++;
					break;
				}
			}
			for(j = 0 ; j < timeQ ; j++)
			{
				if((p[QPeek(&q)-1].count == p[QPeek(&q)-1].CPU_burst))
                                {
                                        p[QPeek(&q)-1].start = i;
                                }

				p[QPeek(&q)-1].count--;
				if(p[QPeek(&q)-1].count == 0)
                                {
					i++;
					if(!QIsEmpty(&q))
					{
						Q = QPeek(&q);
						Dequeue(&q);
                                        	p[Q-1].finish = i;
                                        }
					if(i == p[seq[num]].arrival)
	                                {
                	                        Enqueue(&q,p[seq[num]].process_ID);
                        	                num++;
        	                        }
				break;
                                }
				i++;
				if(j==timeQ-1)
				{
					if(!QIsEmpty(&q))
					{
						Q = QPeek(&q);
						p[Q-1].NO_context++;
						Dequeue(&q);
						flag = 1;
					}
				}
				if(i == p[seq[num]].arrival)
				{
					Enqueue(&q,p[seq[num]].process_ID);
					//printf("arrival ID : %d\n" ,p[seq[num]].process_ID);
					num++;
				}
				if((j==timeQ-1)&&(flag==1))
				{
					Enqueue(&q,Q);
					flag = 0;
					if(QPeek(&q) == Q)
					{
						p[Q-1].NO_context--;
					}
				}
			}
	}				

printf("\n\n     ********************  RR Timequantum : %d  ********************* ",timeQ);
        printf("\n\n pid arrival CPU_burst finish waiting turn around response NO.of context \n\n");
        for(i = 0 ; i < pcount ; i++)
        {
        	p[i].turn_around = p[i].finish - p[i].arrival;
                p[i].waiting = p[i].turn_around - p[i].CPU_burst;
                if(p[i].waiting < 0)
                {
                        p[i].waiting = 0;
                }
                p[i].response = p[i].start-p[i].arrival;
				
                printf(" %3d    %3d     %3d      %3d     %3d      %3d        %3d        %3d\n",p[i].process_ID,p[i].arrival,p[i].CPU_burst,p[i].finish,p[i].waiting,p[i].turn_around,p[i].response,p[i].NO_context);
        sumCPU = sumCPU + p[i].CPU_burst;
        sumwait = sumwait + p[i].waiting;
        sumturn = sumturn + p[i].turn_around;
        sumresponse = sumresponse + p[i].response;
        sumcontext = sumcontext + p[i].NO_context;
        }
	printf("\n\n");
        printf(" Average CPU burst time = %0.2f msm\n",sumCPU/pcount);
        printf(" Average waiting time = %0.2f msm\n",sumwait/pcount);
        printf(" Average turn around time = %0.2f msm\n",sumturn/pcount);
        printf(" Average response time = %0.2f msm\n",sumresponse/pcount);
        printf(" Total NO.of Context Switching Performed time = %d\n",sumcontext);
        printf("\n\n");

       
}
else if(scheduler == 0)
{

	num = 0;
        i=0;
        while(i < total)
        {
		if(i < p[seq[num]].arrival)
		{

                        if((num!=0)&&(p[seq[num-1]].count>1))
                        {
                                i++;
                                break;
                        }
                        else
                        {
                                i++;
                                total++;
                        }
		}
		else if(i >= p[seq[num]].arrival)
		{
		
                        p[seq[num]].start = i;
			Enqueue(&q,p[seq[num]].process_ID);
                        while(1)
                        {
                                if(p[seq[num]].count == 0)
                                {
                                        p[seq[num]].finish = i;
                                        Dequeue(&q);
					num++;
                                        break;
                                }
                                i++;
                                p[seq[num]].count--;
                        }
		}
        
        }
        printf("\n\n           **********************FCFS********************* \n");
        printf("\n\n pid arrival CPU_burst finish waiting turn around response NO.of context \n\n");

	for(i = 0 ; i < pcount ; i++)
        {
                p[i].waiting = p[i].start-p[i].arrival;
                if(p[i].waiting < 0)
                {
                        p[i].waiting = 0;
                }
                p[i].response = p[i].waiting;
                p[i].turn_around = p[i].CPU_burst + p[i].waiting;

                printf(" %3d    %3d     %3d      %3d     %3d      %3d        %3d        %3d\n",p[i].process_ID,p[i].arrival,p[i].CPU_burst,p[i].finish,p[i].waiting,p[i].turn_around,p[i].response,p[i].NO_context);
        sumCPU = sumCPU + p[i].CPU_burst;
        sumwait = sumwait + p[i].waiting;
        sumturn = sumturn + p[i].turn_around;
        sumresponse = sumresponse + p[i].response;
        sumcontext = sumcontext + p[i].NO_context;
        }
	printf("\n\n");
        printf(" Average CPU burst time = %0.2f msm\n",sumCPU/pcount);
        printf(" Average waiting time = %0.2f msm\n",sumwait/pcount);
        printf(" Average turn around time = %0.2f msm\n",sumturn/pcount);
        printf(" Average response time = %0.2f msm\n",sumresponse/pcount);
        printf(" Total NO.of Context Switching Performed time = %d\n",sumcontext);
        printf("\n\n");
	
}
	close(fp);
	close(fp1);
	free(p);
}
