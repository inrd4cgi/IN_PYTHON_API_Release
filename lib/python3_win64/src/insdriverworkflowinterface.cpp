#include "insdriverworkflowinterface.h"

#include "inspersonhandle.h"

namespace INS_INTERFACE
{
	INSDRIVER_EXPORT INQRespondInfo CreateWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
		INSCommonRequest<INQWorkFlowVO, INQWorkFlowVO> commonRequest(5515, workFlowVO);
		commonRequest.WaitForFinished();
		workFlowVO = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo GetWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
		INSCommonRequest<INQWorkFlowVO, qint32> commonRequest(5516, workFlowVO.workFlowId);
		commonRequest.WaitForFinished();
		workFlowVO = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//获取workFlow列表
	INSDRIVER_EXPORT INQRespondInfo
		GetWorkFlowTempls(QList<INQWorkFlowVO> &workFlowVOs, qint32 projectId, qint32 pipelineType) {
		INSCommonRequest<QList<INQWorkFlowVO>, QPair<qint32, qint32>> commonRequest(5517,
			qMakePair(projectId, pipelineType));
		commonRequest.WaitForFinished(-1);
		workFlowVOs = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//更新work-flow,id不为空,name不为空
	INSDRIVER_EXPORT INQRespondInfo UpdateWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
		INSCommonRequest<INQWorkFlowVO, INQWorkFlowVO> commonRequest(5518, workFlowVO);
		commonRequest.WaitForFinished();
		workFlowVO = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//删除work-flow,id不为空
	INSDRIVER_EXPORT INQRespondInfo DeleteWorkFlowTempl(qint32 workFlowId) {
		INSCommonRequest<qint32> commonRequest(5519, workFlowId);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo CreatePrivateUseWorkFlow(INQWorkFlowVO &workFlowVO, qint32 workFlowId) {
		INSCommonRequest<INQWorkFlowVO, qint32> commonRequest(5520, workFlowId);
		commonRequest.WaitForFinished();
		workFlowVO = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INSDRIVER_EXPORT INQRespondInfo GetWorkFlowInstance(INQWorkFlowVO &workFlowVO) {
		//INSCommonRequest<INQWorkFlowVO, qint32> commonRequest(5521, workFlowVO.workFlowId);
		//template <qint32 successCode, typename Recv, typename... Args>
		INSCommonRequest<INQWorkFlowVO, INQWorkFlowVO> commonRequest(5521, workFlowVO);
		commonRequest.WaitForFinished();
		workFlowVO = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//更新work-flow,id不为空,name不为空
	INSDRIVER_EXPORT INQRespondInfo UpdateWorkFlowInstance(INQWorkFlowVO &workFlowVO) {
		INSCommonRequest<INQWorkFlowVO, INQWorkFlowVO> commonRequest(5522, workFlowVO);
		commonRequest.WaitForFinished();
		workFlowVO = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	//创建pipeline step:name和type不能为空,type为1表示shot
	INSDRIVER_EXPORT INQRespondInfo CreatePipelineStep(INPipelineStep &pipelineStep, QVector<INWorkPath> &workPath) {
		INSCommonRequest<QPair<INPipelineStep, QVector<INWorkPath>>, QPair<INPipelineStep, QVector<INWorkPath>>>
			commonRequest(5110, qMakePair(pipelineStep, workPath));
		commonRequest.WaitForFinished();
		pipelineStep = commonRequest.retData.first;
		workPath = commonRequest.retData.second;
		return commonRequest.m_return_value;
	}
	//更新pipeline step:name和id不能为空
	INSDRIVER_EXPORT INQRespondInfo UpdatePipelineStep(INPipelineStep &pipelineStep, QVector<INWorkPath> &workPath) {
		INSCommonRequest<QPair<INPipelineStep, QVector<INWorkPath>>, QPair<INPipelineStep, QVector<INWorkPath>>>
			commonRequest(5111, qMakePair(pipelineStep, workPath));
		commonRequest.WaitForFinished();
		pipelineStep = commonRequest.retData.first;
		workPath = commonRequest.retData.second;
		return commonRequest.m_return_value;
	}
	//根据type获取pipeline step: 若type==0,表示获取全部, type==1表示获取asset,type==2表示获取shot
	INSDRIVER_EXPORT INQRespondInfo
		GetPipelineSteps(QList<INPipelineStep> &pipelineSteps, qint32 pipelineType, qint32 projectId) {
		INSCommonRequest<QList<INPipelineStep>, QPair<qint32, qint32>> commonRequest(5112, qMakePair(pipelineType,
			projectId));
		commonRequest.WaitForFinished();
		pipelineSteps = commonRequest.retData;
		return commonRequest.m_return_value;
	}
	//删除pipeline step:id不能为空
	INSDRIVER_EXPORT INQRespondInfo DeletePipelineStep(qint32 pipelineId) {
		INSCommonRequest<qint32, qint32> commonRequest(5113, pipelineId);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	//批量修改pipeline step 的 surpervisor
	INSDRIVER_EXPORT INQRespondInfo updatePipelineStepSupervisor(qint32 personId, QList<qint32> pipelineSteps) {
		QPair<int, QList<qint32>> param;
		param = qMakePair(personId, pipelineSteps);
		INSCommonRequest<qint32, QPair<int, QList<qint32>>> commonRequest(5114, param);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}

	//批量修改pipeline step 的 coordinator
	INSDRIVER_EXPORT INQRespondInfo updatePipelineStepCoordinator(qint32 personId, QList<qint32> pipelineSteps) {
		QPair<int, QList<qint32>> param;
		param = qMakePair(personId, pipelineSteps);
		INSCommonRequest<qint32, QPair<int, QList<qint32>>> commonRequest(5115, param);
		commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INQRespondInfo GetPipelineStepWorkPath(qint32 pipelineId, QVector<INWorkPath> &workPath)
    {
        INSCommonRequest<QVector<INWorkPath>,qint32> commonRequest(5116,pipelineId);
        commonRequest.WaitForFinished();
        workPath = commonRequest.retData;
        return commonRequest.m_return_value;
    }

	INQRespondInfo GetWorkflowDetailRequiredFiles(qint32 workflowStepId, QList<WorkFlowDetlFile>& detailFiles)
	{
		INSCommonRequest<QList<WorkFlowDetlFile>, qint32> commonRequest(5523, workflowStepId);
		commonRequest.WaitForFinished();
		detailFiles = commonRequest.retData;
		return commonRequest.m_return_value;
	}

	INQRespondInfo UpdateWorkflowDetailRequiredFiles(qint32 workflowStepId,
		QList<WorkFlowDetlFile>& detailFiles)
	{
		INVariadicRequest<0, qint32, qint32, QList<WorkFlowDetlFile>> commonRequest(5524, workflowStepId, detailFiles);
		commonRequest.WaitForFinished();
		return commonRequest.m_return_value;
	}
};
