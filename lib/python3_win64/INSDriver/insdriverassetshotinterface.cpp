#include "insdriverassetshotinterface.h"
#include "inscommonhandle.h"

namespace INS_INTERFACE {

	INSDRIVER_EXPORT MessageInfo GetAssetOrShotReferenceFiles(QMap<qint32, FileVO>& files, qint32 objectId, bool isAsset) {
		INSCommonRequest<QMap<qint32, FileVO>, qint32, bool> commonRequest(333, objectId, isAsset);
		commonRequest.WaitForFinished();
		files = commonRequest.retData;
		return commonRequest.m_return_value;
	}

    INSDRIVER_EXPORT MessageInfo SaveVariantBath(qint32 assetId, const QList<VariantEditParam> &variantEditParams) {
        INSCommonRequest<qint32, qint32, QList<VariantEditParam>> commonRequest(5601, assetId, variantEditParams);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo EditVariant(qint32 assetId, const VariantEditParam &variantEditParam) {
        INSCommonRequest<qint32, qint32, VariantEditParam> commonRequest(5605, assetId, variantEditParam);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo CreateVariant(qint32 assetId, const VariantEditParam &variantEditParam) {
        INSCommonRequest<qint32, qint32, VariantEditParam> commonRequest(5604, assetId, variantEditParam);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo DeleteVariantById(qint32 variantId) {
        INSCommonRequest<qint32, qint32> commonRequest(5606, variantId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo GetVariantByAssetId(QList<VariantVO> &variants, qint32 assetId) {
        INSCommonRequest<QList<VariantVO>, qint32> commonRequest(5602, assetId);
        commonRequest.WaitForFinished();
        variants = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo GetVariantRecordByAssetId(QList<VariantRecordVO> &variantRecords, qint32 assetId) {
        INSCommonRequest<QList<VariantRecordVO>, qint32> commonRequest(5603, assetId);
        commonRequest.WaitForFinished();
        variantRecords = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT qint32 GetAssetsByCondition(QList<INAsset> &assets, const AssetFilterParam &assetFilterParam) {
        INSCommonRequest<QList<INAsset>, AssetFilterParam> commonRequest(541, assetFilterParam);
        commonRequest.WaitForFinished();
        assets = commonRequest.retData;
        return commonRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT qint32
    GetAssetsPipelineStepMode(QMap<qint32, QList<INTask>> &assets, const AssetFilterParam &assetFilterParam) {
        INSCommonRequest<QMap<qint32, QList<INTask>>, AssetFilterParam> commonRequest(545, assetFilterParam);
        commonRequest.WaitForFinished();
        assets = commonRequest.retData;
        return commonRequest.m_return_value.code;
    }

    INSDRIVER_EXPORT qint32 GetShotsByCondition(QList<INShot> &shots, const ShotFilterParam &shotFilterParam) {
        INSCommonRequest<QList<INShot>, ShotFilterParam> commonRequest(561, shotFilterParam);
        commonRequest.WaitForFinished();
        shots = commonRequest.retData;
        return commonRequest.m_return_value.code;
    }

    //获取资产信息
    INSDRIVER_EXPORT qint32
    GetShotListPipelineStepMode(QMap<qint32, QList<INTask>> &shots, const ShotFilterParam &shotFilterParam) {
        INSCommonRequest<QMap<qint32, QList<INTask>>, ShotFilterParam> commonRequest(567, shotFilterParam);
        commonRequest.WaitForFinished();
        shots = commonRequest.retData;
        return commonRequest.m_return_value.code;
    }

    //创建资产
    INSDRIVER_EXPORT MessageInfo CreateAsset(INAsset &newasset, QList<TagParam> taglist) {
        INSCommonRequest<INAsset, INAsset, QList<TagParam>> commonRequest(542, newasset, taglist);
        commonRequest.WaitForFinished();
        newasset = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //编辑资产信息
    INSDRIVER_EXPORT MessageInfo EditAsset(INAsset &easset) {

        INSCommonRequest<INAsset, INAsset> commonRequest(543, easset);
        commonRequest.WaitForFinished();
        easset = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //删除资产信息
    INSDRIVER_EXPORT MessageInfo DeleteAsset(int assetId) {
        INSCommonRequest<qint32, qint32> commonRequest(544, assetId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    //获取资产状态列表
    INSDRIVER_EXPORT QList<INAssetStatus> GetAssetStatusList() {
        return INAssetStatusOperate::GetAssetStatusList();
    }

    INSDRIVER_EXPORT QString GetAssetStateString(INAssetStatus assetState) {
        return INAssetStatusOperate::GetINAssetStatusString(assetState);
    }

    //获取特定权限的人员列表
    INSDRIVER_EXPORT MessageInfo GetPersonsInAction(QSet<QPair<qint32, QString>> &ret, PersonInActionParam param) {
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
        assetFilterParam.assetIds = {assetinfo.assetId};
        auto ret = GetAssetsByCondition(assets, assetFilterParam);
        assetinfo = assets.isEmpty() ? INAsset() : assets[0];
        return ret;
    }

    //创建镜头
    INSDRIVER_EXPORT MessageInfo CreateShot(INShot &newshot, QList<TagParam> taglist) {
        INSCommonRequest<INShot, INShot, QList<TagParam>> commonRequest(562, newshot, taglist);
        commonRequest.WaitForFinished();
        newshot = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //编辑镜头信息
    INSDRIVER_EXPORT MessageInfo EditShot(INShot &eshot) {
        INSCommonRequest<INShot, INShot> commonRequest(563, eshot);
        commonRequest.WaitForFinished();
        eshot = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //删除镜头
    INSDRIVER_EXPORT MessageInfo DeleteShot(int shotId) {

        INSCommonRequest<qint32, qint32> commonRequest(564, shotId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    //获取场景列表
    INSDRIVER_EXPORT qint32 GetSceneList(int projectId, QMap<qint32, QString> &scenelist) {

        INSCommonRequestRetInt<QMap<qint32, QString>, int> commonRequest(565, projectId);
        commonRequest.WaitForFinished();
        scenelist = commonRequest.retData;
        return commonRequest.m_return_value;

    }

    //获取场景列表
    INSDRIVER_EXPORT MessageInfo GetSceneList(int projectId, QMap<qint32, INSceneVO> &scenes) {

		INSCommonRequest<QMap<qint32, INSceneVO>, int> commonRequest(568, projectId);
        commonRequest.WaitForFinished();
        scenes = commonRequest.retData;
        return commonRequest.m_return_value;

    }

    //创建场景
    INSDRIVER_EXPORT qint32 CreateScene(QString sceneName, int projectId, int &sceneId) {

        INSCommonRequestRetInt<int, QString, int> commonRequest(566, sceneName, projectId);
        commonRequest.WaitForFinished();
        sceneId = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //获取某一Shot和Shot下的task
    INSDRIVER_EXPORT qint32 GetShotInfo(INShot &shotinfo) {
        QList<INShot> shots;
        ShotFilterParam shotFilterParam;
        shotFilterParam.shotIds = {shotinfo.shotId};
        auto ret = GetShotsByCondition(shots, shotFilterParam);
        shotinfo = shots.isEmpty() ? INShot() : shots[0];
        return ret;
    }

    //获取回收站列表
    INSDRIVER_EXPORT qint32 GetBusRecycleBinList(QList<RecycleInfo> &recyclebinList) {

        INSCommonRequestRetInt<QList<RecycleInfo>, QList<RecycleInfo>> commonRequest(800, recyclebinList);
        commonRequest.WaitForFinished();
        recyclebinList = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //删除回收站某一条记录
    INSDRIVER_EXPORT qint32 DeleteObjectInRecordBin(qint32 recordId) {

        INSCommonRequestRetInt<qint32, qint32> commonRequest(801, recordId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    //恢复回收站某一条记录
    INSDRIVER_EXPORT qint32 RestoreObjectInRecordBin(qint32 recordId) {

        INSCommonRequestRetInt<qint32, qint32> commonRequest(802, recordId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }
};
