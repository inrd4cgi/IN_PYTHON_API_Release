#include "insdriverassetshotinterface.h"
#include "insasset.h"
#include "insshot.h"
#include "inspersonhandle.h"
#include "insrecyclebin.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT qint32 GetAssetsByCondition(QList<INAsset>& assets, const AssetFilterParam& assetFilterParam) {
		INSCommonRequest<QList<INAsset>, AssetFilterParam> commonRequest(541, assetFilterParam);
		commonRequest.WaitForFinished();
		assets = commonRequest.retData;
		return commonRequest.m_return_value.code;
	}

	INSDRIVER_EXPORT qint32
	GetAssetsPipelineStepMode(QMap<qint32, QList<INTask>> &assets, const AssetFilterParam& assetFilterParam) {
		INSCommonRequest<QMap<qint32, QList<INTask>>, AssetFilterParam> commonRequest(545, assetFilterParam);
		commonRequest.WaitForFinished();
		assets = commonRequest.retData;
		return commonRequest.m_return_value.code;
	}

	INSDRIVER_EXPORT qint32 GetShotsByCondition(QList<INShot>& shots, const ShotFilterParam& shotFilterParam) {
		INSCommonRequest<QList<INShot>, ShotFilterParam> commonRequest(561, shotFilterParam);
		commonRequest.WaitForFinished();
		shots = commonRequest.retData;
		return commonRequest.m_return_value.code;
	}

	//获取资产信息
	INSDRIVER_EXPORT qint32
	GetShotListPipelineStepMode(QMap<qint32, QList<INTask>> &shots, const ShotFilterParam& shotFilterParam) {
		INSCommonRequest<QMap<qint32, QList<INTask>>, ShotFilterParam> commonRequest(567, shotFilterParam);
		commonRequest.WaitForFinished();
		shots = commonRequest.retData;
		return commonRequest.m_return_value.code;
	}

	//创建资产
	INSDRIVER_EXPORT qint32 CreateAsset(INAsset &newasset, QList<TagParam> taglist) {
		INSCreateAsset newassetobj(newasset, taglist);
		newassetobj.WaitForFinished();
		newasset = newassetobj.m_newasset;
		return newassetobj.m_return_value;
	}

	//编辑资产信息
	INSDRIVER_EXPORT qint32 EditAsset(INAsset &easset) {
		INSEditAsset editassetobj(easset);
		editassetobj.WaitForFinished();
		return editassetobj.m_return_value;
	}

	//删除资产信息
    INSDRIVER_EXPORT INQRespondInfo DeleteAsset(int assetId) {
		INSDeleteAsset delassetobj(assetId);
		delassetobj.WaitForFinished();
		return delassetobj.m_return_value;
	}

	//获取资产状态列表
	INSDRIVER_EXPORT QList<INAssetStatus> GetAssetStatusList() {
		return INAssetStatusOperate::GetAssetStatusList();
	}

	INSDRIVER_EXPORT QString GetAssetStateString(INAssetStatus assetState) {
		return INAssetStatusOperate::GetINAssetStatusString(assetState);
	}

	//获取特定权限的人员列表
	INSDRIVER_EXPORT INQRespondInfo  GetPersonsInAction(QSet<QPair<qint32, QString>> &ret, PersonInActionParam param) {
		INSCommonRequest<QSet<QPair<qint32, QString>>, PersonInActionParam> commonRequest(213, param);
		commonRequest.WaitForFinished();
		ret = commonRequest.retData;
		return commonRequest.m_return_value;
	}

    //获取某一Asset和Asset下的task
    /*!
     * \brief GetGetShotInfo资产信息
     * \param assetinfo
     * \return [1]：获取成功\n
     *         [0]:获取失败
     */
	INSDRIVER_EXPORT qint32 GetAssetInfo(INAsset &assetinfo) {
		QList<INAsset> assets;
		AssetFilterParam assetFilterParam;
		assetFilterParam.assetIds = { assetinfo.assetId};
		auto ret= GetAssetsByCondition(assets,assetFilterParam);
		assetinfo = assets.isEmpty() ? INAsset() : assets[0];
		return ret;
	}

	//创建镜头
	INSDRIVER_EXPORT qint32 CreateShot(INShot &newshot, QList<TagParam> taglist) {
		INSCreateShot newshotobj(newshot, taglist);
		newshotobj.WaitForFinished();
		newshot = newshotobj.m_newshot;
		return newshotobj.m_return_value;
	}

	//编辑镜头信息
	INSDRIVER_EXPORT qint32 EditShot(INShot &eshot) {
		INSEditShot editshotobj(eshot);
		editshotobj.WaitForFinished();
		return editshotobj.m_return_value;
	}

	//删除镜头
    INSDRIVER_EXPORT INQRespondInfo DeleteShot(int shotId) {
		INSDeleteShot delShotobj(shotId);
		delShotobj.WaitForFinished();
		return delShotobj.m_return_value;
	}

	//获取场景列表
	INSDRIVER_EXPORT qint32 GetSceneList(int projectId, QMap<qint32, QString> &scenelist) {
		INSGetSceneList getscenelistobj(projectId);
		getscenelistobj.WaitForFinished();
		scenelist = getscenelistobj.m_scenelist;
		return getscenelistobj.m_return_value;
	}

	//创建场景
	INSDRIVER_EXPORT qint32 CreateScene(QString sceneName, int projectId, int &sceneId) {
		INSCreateScene newscene(sceneName, projectId);
		newscene.WaitForFinished();
		sceneId = newscene.m_sceneId;
		return newscene.m_return_value;
	}

	//获取某一Shot和Shot下的task
	INSDRIVER_EXPORT qint32 GetShotInfo(INShot &shotinfo) {
		QList<INShot> shots;
		ShotFilterParam shotFilterParam;
		shotFilterParam.shotIds = { shotinfo.shotId };
		auto ret= GetShotsByCondition(shots, shotFilterParam);
		shotinfo = shots.isEmpty() ? INShot() : shots[0];
		return ret;
	}

	//获取回收站列表
	INSDRIVER_EXPORT qint32 GetBusRecycleBinList(QList<DeleteInfo> &recyclebinList) {
		INSGetBusRecycleList getlistobj(recyclebinList);
		getlistobj.WaitForFinished();
		recyclebinList = getlistobj.m_delInfoList;
		return getlistobj.m_return_value;
	}

	//删除回收站某一条记录
    INSDRIVER_EXPORT qint32 DeleteObjectInRecordBin(qint32 recordId) {
		INSDeleteObjInRecordBin delObj(recordId);
		delObj.WaitForFinished();
        return delObj.m_return_value;
	}

    //恢复回收站某一条记录
    INSDRIVER_EXPORT qint32 RestoreObjectInRecordBin(qint32 recordId) {
		INSRestoreObjInRecordBin restoreObj(recordId);
		restoreObj.WaitForFinished();
        return restoreObj.m_return_value;
    }
};
