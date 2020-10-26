#pragma once

#include "insdatastructure.h"
#include "insdriver_global.h"
#include "InTaskStatus.h"

namespace INS_INTERFACE
{

	INSDRIVER_EXPORT qint32 GetAssetsByCondition(QList<INAsset>& assets,const AssetFilterParam& assetFilterParam);

    INSDRIVER_EXPORT qint32 GetAssetsPipelineStepMode(QMap<qint32, QList<INTask>> &assets, const AssetFilterParam& assetFilterParam);

	INSDRIVER_EXPORT qint32 GetShotsByCondition(QList<INShot>& shots, const ShotFilterParam& shotFilterParam);

    INSDRIVER_EXPORT qint32 GetShotListPipelineStepMode(QMap<qint32, QList<INTask>> &shots, const ShotFilterParam& shotFilterParam);

	//创建资产
	INSDRIVER_EXPORT qint32 CreateAsset(INAsset& newasset, QList<TagParam> taglist);

	//编辑资产信息
	INSDRIVER_EXPORT qint32 EditAsset(INAsset& easset);

	//删除资产信息
    INSDRIVER_EXPORT INQRespondInfo DeleteAsset(int assetId);

	//获取资产状态列表
	INSDRIVER_EXPORT QList<INAssetStatus> GetAssetStatusList();

	INSDRIVER_EXPORT QString GetAssetStateString(INAssetStatus assetState);

	//获取特定权限的人员列表
	INSDRIVER_EXPORT INQRespondInfo GetPersonsInAction(QSet<QPair<qint32, QString>> &ret, PersonInActionParam param);

	//获取某一Asset和Asset下的task
    INSDRIVER_EXPORT qint32 GetAssetInfo(INAsset& assetinfo);

	//创建镜头
	INSDRIVER_EXPORT qint32 CreateShot(INShot& newshot, QList<TagParam> taglist);

	//编辑镜头信息
	INSDRIVER_EXPORT qint32 EditShot(INShot& eshot);

	//删除镜头
    INSDRIVER_EXPORT INQRespondInfo DeleteShot(int shotId);

	//获取场景列表
	INSDRIVER_EXPORT qint32 GetSceneList(int projectId, QMap<qint32, QString>& scenelist);

	//创建场景
	INSDRIVER_EXPORT qint32 CreateScene(QString sceneName, int projectId, int& sceneId);

	//获取某一Shot和Shot下的task
	INSDRIVER_EXPORT qint32 GetShotInfo(INShot& shotinfo);

	//asset/shot/task回收站部分
	INSDRIVER_EXPORT qint32 GetBusRecycleBinList(QList<DeleteInfo> &recyclebinList);

    //删除回收站某一条记录
    INSDRIVER_EXPORT qint32 DeleteObjectInRecordBin(qint32 recordId);

    //恢复回收站某一条记录
    INSDRIVER_EXPORT qint32 RestoreObjectInRecordBin(qint32 recordId);
};