  #include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

struct CARDATA
{
	string plateName;
	string typeName;	
};
   
int read_car(string plateMarkPath,string typeMarkPath,int& nplate,int& ntype,vector<CARDATA>& carDataMark)
{	
	fstream fplatemark;
	fplatemark.open(plateMarkPath,ios::in);
	if(!fplatemark.is_open())
	{
		cout << "plate 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}
	char line[128];
	vector<string>plateMark;
	while(fplatemark.getline(line,sizeof(line)))
	{
		string plateName=line;
		plateMark.push_back(plateName);
		if(plateName!="no")
		{
			nplate++;
		}
	}

	fplatemark.close();

	fstream ftypemark;
	ftypemark.open(typeMarkPath,ios::in);
	if(!ftypemark.is_open())
	{
		cout << "type 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	vector<string>typeMark;	
	while(fplatemark.getline(line,sizeof(line)))
	{
		string typeName=line;
		typeMark.push_back(typeName);
		if(typeName!="no")
		{
			ntype++;
		}
	}
	ftypemark.close();

	if(plateMark.size()!=typeMark.size())
	{
		printf("标记的车辆中的车牌个数和车型个数不相等");
		system("pause");
	}
	
	for(int i=0;i<plateMark.size();i++)
	{
		CARDATA card;
		string plateName=plateMark[i];
		card.plateName=plateName;
		string typeName=typeMark[i];
		card.typeName=typeName;
	}
	return 0;
}
int compare_car(vector<CARDATA>carMark,vector<CARDATA>carDetect)
{
	int rightPlateNum=0;
	
	int plate_leak_error_num=0; int alarm_error_num=0;

	for(int i=0;i<carMark.size();i++)
	{
		string plateMarkName=carMark[i].plateName;
		string typeMarkName=carMark[i].typeName;
		int flagHave=0;
		for(int j=0;j<carDetect.size();j++)
		{
			string plateDetectName=carDetect[j].plateName;
			string typeDetectName=carDetect[j].typeName;
			if(strcmp(plateMarkName.c_str(),plateDetectName.c_str())==0)
			{
				rightPlateNum++;
				flagHave=1;
				break;
			}
			
		}
		

	}
	return 0;
}
int test10_1(int argc, char *argv[])
{
	string plateMarkPath="plate.txt";
	string typeMarkPath="type.txt";
	int nmplate=0; int nmtype=0;
	vector<CARDATA> carDataMark;
	read_car(plateMarkPath,typeMarkPath,nmplate,nmtype,carDataMark);


	string plateDetectPath="0_plate.txt";
	string typeDetectPath="0_type.txt";
	int ndplate=0; int ndtype=0;
	vector<CARDATA> carDataDetect;
	read_car(plateDetectPath,typeDetectPath,ndplate,ndtype,carDataDetect);

	return 0;
}

int compare_plate(vector<string>plateMark,vector<string>plateDetect)
{

	
	string pathLeakError="leak_error.txt";

	fstream fleakerror;
	fleakerror.open(pathLeakError,ios::out);
	if(!fleakerror.is_open())
	{
		 cout << "ferror 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}
	  
	


	int markNum=plateMark.size();
	int detectNum=plateDetect.size();
	int rightNum=0;int errorNum=0;int leakNum=0;int alarmNum=0;
	  int rightNum1=0;
	int leak_error_num=0; int alarm_error_num=0;
	for(int i=0;i<plateMark.size();i++)
	{
		string markName=plateMark[i];
		int flagHave=0;
		for(int j=0;j<plateDetect.size();j++)
		{
			 string detectName=plateDetect[j];
			 if(strcmp(markName.c_str(),detectName.c_str())==0)
			 {
				  rightNum++;
				   flagHave=1;
				   break;
			 }
		}
		if(flagHave==0)
		{
			leak_error_num++;
		   fleakerror<<markName<<endl;
		}

	}
    fleakerror.close();

	if(leak_error_num!=(markNum-rightNum))
	{
		printf("程序有bug!\n");
		system("pause");
	}

	for(int i=0;i<plateDetect.size();i++)
	{
		string detectName=plateDetect[i];
		int flagHave=0;
		for(int j=0;j<plateMark.size();j++)
		{
			string markName=plateMark[j];
			if(strcmp(markName.c_str(),detectName.c_str())==0)
			{
				rightNum1++;
				  flagHave=1;
				  break;
			}
		}
	   if(flagHave==0)
	   {
			  alarm_error_num++;
	   }

	}

	if(alarm_error_num!=(detectNum-rightNum1))
	{
		printf("程序有1bug!\n");
		system("pause");
	}
	if (rightNum1 != rightNum)
	{
	//	printf("程序有2bug!\n");
	//system("pause");
	}


	 int plateNum = plateMark.size();
	printf("标记数=%d,检测数=%d,正确数=%d\n",
		plateNum, detectNum, rightNum);

	float right_ratio = rightNum * 1.0 / plateNum;
	float right_ratio1 = rightNum * 1.0 / detectNum;

	printf("正确率=%0.4f;正确率1=%0.4f\n", right_ratio, right_ratio1);

		
		
	return 0;
}

int test10(int argc, char *argv[])
{

	//string pathMark="车辆test2.txt";
	//string pathDetect="0_plate_gpu.txt";

	string pathMark="plate.txt";
	string pathDetect="0_plate_gpu.txt";

	fstream fmark;
	fmark.open(pathMark,ios::in);
	if(!fmark.is_open())
	{
		 cout << "文件数据打开错误！" << endl;
		system("pause");
		return false;
	}
	  
	fstream fdetect;
	fdetect.open(pathDetect,ios::in);
	if(!fdetect.is_open())
	{
		 cout << "文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	vector<string>plateMark;
	vector<string>plateDetect;

	char line[128];
	while(fmark.getline(line,sizeof(line)))
	{
		  string plateName=line;
		  plateMark.push_back(plateName);
	}
	fmark.close();

   
	while(fdetect.getline(line,sizeof(line)))
	{
		  string plateName=line;
		  plateDetect.push_back(plateName);
	}
	fdetect.close();

	  compare_plate(plateMark,plateDetect);

	return 0;
}

