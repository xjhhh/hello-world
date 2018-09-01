#include<stdio.h>
#include<string.h>

struct Student
{
	char name[10];
	char sex[10];
	int age;
	char city[10];
	char grade[10];
};

int main()
{

	struct Student stu1;
	printf("请输入性别:");
	scanf_s("%s", &stu1.sex,10);
	printf("%d",strlen(stu1.sex));

	printf("请输入年龄:");
	scanf_s("%d", &stu1.age,4);

	printf("请输入城市:");
	printf("%d",scanf_s("%s", &stu1.city,10));

	printf("请输入年级:");
	printf("%d",scanf("%s", &stu1.grade,10));

	printf("请输入姓名:");
	scanf_s("%s", &stu1.name,10);

	printf("姓名：%s  首地址：%x\n", stu1.name, &stu1.name);
	printf("性别：%s  首地址：%x\n", stu1.sex, &stu1.sex);
	printf("年龄：%d  首地址：%x\n", stu1.age, &stu1.age);
	printf("城市：%s  首地址：%x\n", stu1.city, &stu1.city);
	printf("年级：%s  首地址：%x\n", stu1.grade, &stu1.grade);

	return 0;
}
