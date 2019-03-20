#include "mrc_base.h" 
#include "mrc_win.h"
#include "mrc_exb.h"
#include "mrp.h"


char *mrpfile;



void Demo1WinWinEvent(int32 data, int32 eventId)
{
    switch (eventId)
    {
    case WIN_EVENT_SHOW:
    case WIN_EVENT_REFRESH:	
        break;
    case WIN_EVENT_PAUSE:
        break;
    case WIN_EVENT_EXIT:
        break;
    case WIN_EVENT_UPDATE:
        break;
    }
}
void progbar(uint8 value, uint8 error)
{
	char *temp;

	switch(value)
	{
	case 1:
		ShowLineText(0,"启动打包模块...",248,0,0);
		break;
	case 2:
		ShowLineText(1,"开始搜索文件...",248,0,0);
		break;
	case 3:
		ShowLineText(1,"开始写文件头...",248,0,0);
		break;
	case 4:
		ShowLineText(1,"创建文件列表...",248,0,0);
		break;
	case 5:
		ShowLineText(1,"读入文件数据...",248,0,0);
		break;
	case 6:
		ShowLineText(1,"更新文件信息...",248,0,0);
		break;
	case 7:
		if(error)
		{
			temp = (char*)malloc(50);
			mrc_sprintf(temp,"出现了%d个错误",error);
			ShowLineText(1,temp,248,0,0);
			mrc_free((void*)temp);
		}
		break;
	}
}
void dabao(void)
{
	int32 ret=0;
	char *aa="我的MRP程序";
	TOMRPINFO MRPinfo;

	MRPinfo.appid = 1000;//APPID
	MRPinfo.version = 1001;//版本ID
	MRPinfo.appname = aa;
	MRPinfo.description = aa;
	MRPinfo.filename = "MyMrp.mrp";
	MRPinfo.vendor = "默水瓶";

	ret = ToMrp("./temp","./MyMrp.mrp",204800, &MRPinfo, progbar);
	switch(ret)
	{
	case MRP_SUCCESS:
		ShowLineText(1,"打包操作成功！",255,255,255);
		return;
	case MRP_SEARCHFAILED:
		ShowLineText(1,"无法搜索文件！",255,255,255);
		break;
	case MRP_OPENFAILED:
		ShowLineText(1,"无法打开文件！",255,255,255);
		break;
	case MRP_LISTLENFAILED:
		ShowLineText(1,"没有找到文件！",255,255,255);
		break;
	default:
		break;
	}
	ShowLineText(1,"打包操作失败！",255,255,255);
}

void jb(void)
{		
	if(MR_FAILED != UnMrp(mrpfile,"temp",204800))
	{
// 解包完成！
    }
}
void jy(void)
{			
	if(MR_FAILED != UnMrp(mrpfile,"temp",204800))
	{
		//解压完成！
	}
	else
	{
		//解压失败！
	}
}



void Demo1KeyWinEvent(int32 data, int32 type, int32 p1, int32 p2)
{
	if(MR_KEY_PRESS == type)
	{
		switch(p1)
		{
		case MR_KEY_1://解压
			jy();
			return;
		case MR_KEY_2://提取
			jb();
			return;
		case MR_KEY_3:
            dabao();
			return;
		default:
			return;
		}
	}
}

int32 mrc_init(void)
{
    mrpfile="1.mrp";
	mrc_winInit();
	mrc_winNew(0, Demo1WinWinEvent, Demo1KeyWinEvent);
	return MR_SUCCESS;
}

int32 mrc_appEvent(int32 code, int32 param0, int32 param1)
{
	mrc_winEvent(code, param0, param1);
	return MR_SUCCESS;
}


int32 mrc_appPause(void)
{
	return 0;
}


int32 mrc_appResume(void)
{
	mrc_winResume();
	return 0;
}


int32 mrc_exitApp(void)
{
	return 0;
}