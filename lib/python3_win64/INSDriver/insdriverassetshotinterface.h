#pragma once

#include "insdatastructure.h"
#include "insdriver_global.h"
#include "InTaskStatus.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT MessageInfo SetTaskToValidate(qint32 taskId,qint32 toValidate, const QPair<QString,QString>& pyPath);

	INSDRIVER_EXPORT MessageInfo AddPipelineStepMatchedGroup(const PipelineStepMappingEditParam &mappingEditParam);

	INSDRIVER_EXPORT MessageInfo EditPipelineStepMatchedGroup(qint32 mappingId, const QSet<qint32> &newPathIds);

	INSDRIVER_EXPORT MessageInfo
		GetPipelineStepMatchedGroupByProjectId(QMap<qint32, PipelineStepMappingVO>& retRsult,qint32 projectId);

	INSDRIVER_EXPORT MessageInfo DeletePipelineStepMatchedGroupByMappingId(qint32 mappingId);

	//使用篇///////////////////////////////////////////////////////////////////////////////
	INSDRIVER_EXPORT MessageInfo AddAsset2Shot(qint32 shotId, qint32 assetId, qint32 variantId);

	INSDRIVER_EXPORT MessageInfo DeleteAssetInShot(qint32 shotId, qint32 assetId, qint32 variantId);

	//first assetId second variantId
	INSDRIVER_EXPORT MessageInfo DeleteAssetsInShot(qint32 shotId,const QSet<QPair<qint32, qint32>>& assetVariants);

	INSDRIVER_EXPORT MessageInfo GetShotMatchedState(QList<TaskPipelineStepMappingStateVO>& retRsult,qint32 shotId, qint32 assetId, qint32 variantId);

	INSDRIVER_EXPORT MessageInfo IgnoreWarning(qint32 shotId, qint32 assetId, qint32 variantId);

	INSDRIVER_EXPORT MessageInfo GetShotAssetMappingView(QMap<qint32, ShotAssetMappingView>& retResult,ShotFilterParam shotFilterParam);

	// 到此为止 ////
	INSDRIVER_EXPORT MessageInfo GetAssetOrShotReferenceFiles(QMap<qint32,FileVO>& files, qint32 objectId, bool isAsset = true);

	//////variant//////
	//批量操作
	INSDRIVER_EXPORT MessageInfo SaveVariantBath(qint32 assetId, const QList<VariantEditParam> &variantEditParams);

	INSDRIVER_EXPORT MessageInfo EditVariant(qint32 assetId, const VariantEditParam &variantEditParam);

	INSDRIVER_EXPORT MessageInfo CreateVariant(qint32 assetId, const VariantEditParam &variantEditParam);

	INSDRIVER_EXPORT MessageInfo DeleteVariantById(qint32 variantId);

	INSDRIVER_EXPORT MessageInfo GetVariantByAssetId(QList<VariantVO>& variants, qint32 assetId);

	INSDRIVER_EXPORT MessageInfo GetVariantRecordByAssetId(QList<VariantRecordVO>& variantRecords, qint32 assetId);

	//////variant//////
	INSDRIVER_EXPORT qint32 GetAssetsByCondition(QList<INAsset>& assets,const AssetFilterParam& assetFilterParam);

    INSDRIVER_EXPORT qint32 GetAssetsPipelineStepMode(QMap<qint32, QList<INTask>> &assets, const AssetFilterParam& assetFilterParam);

	INSDRIVER_EXPORT qint32 GetShotsByCondition(QList<INShot>& shots, const ShotFilterParam& shotFilterParam);

    INSDRIVER_EXPORT qint32 GetShotListPipelineStepMode(QMap<qint32, QList<INTask>> &shots, const ShotFilterParam& shotFilterParam);

	//创建资产
    INSDRIVER_EXPORT MessageInfo CreateAsset(INAsset& newasset, QList<TagParam> taglist);

	//编辑资产信息
    INSDRIVER_EXPORT MessageInfo EditAsset(INAsset& easset);

	//删除资产信息
    INSDRIVER_EXPORT MessageInfo DeleteAsset(int assetId);

	//获取资产状态列表
	INSDRIVER_EXPORT QList<INAssetStatus> GetAssetStatusList();

	INSDRIVER_EXPORT QString GetAssetStateString(INAssetStatus assetState);

	//获取特定权限的人员列表
	INSDRIVER_EXPORT MessageInfo GetPersonsInAction(QSet<QPair<qint32, QString>> &ret, PersonInActionParam param);

	//获取某一Asset和Asset下的task
    INSDRIVER_EXPORT qint32 GetAssetInfo(INAsset& assetinfo);

	//创建镜头
    INSDRIVER_EXPORT MessageInfo CreateShot(INShot& newshot, QList<TagParam> taglist);

	//编辑镜头信息
    INSDRIVER_EXPORT MessageInfo EditShot(INShot& eshot);

	//删除镜头
    INSDRIVER_EXPORT MessageInfo DeleteShot(int shotId);

	//获取场景列表
	INSDRIVER_EXPORT qint32 GetSceneList(int projectId, QMap<qint32, QString>& scenelist);

    //获取场景列表
    INSDRIVER_EXPORT MessageInfo GetSceneList(int projectId, QMap<qint32, INSceneVO> &scenes);

	//创建场景
	INSDRIVER_EXPORT qint32 CreateScene(QString sceneName, int projectId, int& sceneId);

	//获取某一Shot和Shot下的task
	INSDRIVER_EXPORT qint32 GetShotInfo(INShot& shotinfo);

	//asset/shot/task回收站部分
	INSDRIVER_EXPORT MessageInfo GetBusRecycleBinList(int projectId, QList<RecycleInfo> &recyclebinList);

    //删除回收站某一条记录
    INSDRIVER_EXPORT MessageInfo DeleteObjectInRecordBin(qint32 recordId);

    //恢复回收站某一条记录
    INSDRIVER_EXPORT MessageInfo RestoreObjectInRecordBin(qint32 recordId);
};
