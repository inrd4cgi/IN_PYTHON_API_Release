#include "insdriverworkflowinterface.h"

#include "inscommonhandle.h"

namespace INS_INTERFACE {
    INSDRIVER_EXPORT MessageInfo CreateWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
        INSCommonRequest<INQWorkFlowVO, INQWorkFlowVO> commonRequest(5515, workFlowVO);
        commonRequest.WaitForFinished();
        workFlowVO = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo GetWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
        INSCommonRequest<INQWorkFlowVO, qint32> commonRequest(5516, workFlowVO.workFlowId);
        commonRequest.WaitForFinished();
        workFlowVO = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //获取workFlow列表
    INSDRIVER_EXPORT MessageInfo
    GetWorkFlowTempls(QList<INQWorkFlowVO> &workFlowVOs, qint32 projectId, qint32 pipelineType) {
        INSCommonRequest<QList<INQWorkFlowVO>, qint32, qint32> commonRequest(5517, projectId, pipelineType);
        commonRequest.WaitForFinished(-1);
        workFlowVOs = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //更新work-flow,id不为空,name不为空
    INSDRIVER_EXPORT MessageInfo UpdateWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
        INSCommonRequest<INQWorkFlowVO, INQWorkFlowVO> commonRequest(5518, workFlowVO);
        commonRequest.WaitForFinished();
        workFlowVO = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //删除work-flow,id不为空
    INSDRIVER_EXPORT MessageInfo DeleteWorkFlowTempl(qint32 workFlowId) {
        INSCommonRequest<qint32, qint32> commonRequest(5519, workFlowId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    INSDRIVER_EXPORT MessageInfo CreatePrivateUseWorkFlow(INQWorkFlowVO &workFlowVO, qint32 workFlowId) {
        INSCommonRequest<INQWorkFlowVO, qint32> commonRequest(5520, workFlowId);
        commonRequest.WaitForFinished();
        workFlowVO = commonRequest.retData;
        return commonRequest.m_return_value;
    }

//    INSDRIVER_EXPORT MessageInfo GetWorkFlowInstance(INQWorkFlowVO &workFlowVO) {
//        //INSCommonRequest<INQWorkFlowVO, qint32> commonRequest(5521, workFlowVO.workFlowId);
//        //template <qint32 successCode, typename Recv, typename... Args>
//        INSCommonRequest<INQWorkFlowVO, INQWorkFlowVO> commonRequest(5521, workFlowVO);
//        commonRequest.WaitForFinished();
//        workFlowVO = commonRequest.retData;
//        return commonRequest.m_return_value;
//    }

    INSDRIVER_EXPORT MessageInfo GetWorkFlowInstance(TaskWorkflow& taskWorkflow, qint32 objectID, qint32 objectType)
    {
        INSCommonRequest<TaskWorkflow, qint32, qint32> commonRequest(5521, objectID, objectType);
        commonRequest.WaitForFinished();
        taskWorkflow = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //更新work-flow,id不为空,name不为空
    INSDRIVER_EXPORT MessageInfo UpdateWorkFlowInstance(TaskWorkflow & taskWorkflow) {
        INSCommonRequest<TaskWorkflow, TaskWorkflow> commonRequest(5522, taskWorkflow);
        commonRequest.WaitForFinished();
        taskWorkflow = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    //创建pipeline step:name和type不能为空,type为1表示shot
    INSDRIVER_EXPORT MessageInfo CreatePipelineStep(INPipelineStep &pipelineStep) {
        INSCommonRequest<INPipelineStep, INPipelineStep> commonRequest(5110, pipelineStep);
        commonRequest.WaitForFinished();
        pipelineStep = commonRequest.retData;
        return commonRequest.m_return_value;
    }
    //更新pipeline step:name和id不能为空
    INSDRIVER_EXPORT MessageInfo UpdatePipelineStep(INPipelineStep &pipelineStep) {
        INSCommonRequest<INPipelineStep, INPipelineStep> commonRequest(5111, pipelineStep);
        commonRequest.WaitForFinished();
        pipelineStep = commonRequest.retData;
        return commonRequest.m_return_value;
    }
    //根据type获取pipeline step: 若type==0,表示获取全部, type==1表示获取asset,type==2表示获取shot
    INSDRIVER_EXPORT MessageInfo
    GetPipelineSteps(QList<INPipelineStep> &pipelineSteps, qint32 pipelineType, qint32 projectId) {
        INSCommonRequest<QList<INPipelineStep>, qint32, qint32> commonRequest(5112, pipelineType, projectId);
        commonRequest.WaitForFinished();
        pipelineSteps = commonRequest.retData;
        return commonRequest.m_return_value;
    }
    //删除pipeline step:id不能为空
    INSDRIVER_EXPORT MessageInfo DeletePipelineStep(qint32 pipelineId) {
        INSCommonRequest<qint32, qint32> commonRequest(5113, pipelineId);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    //批量修改pipeline step 的 surpervisor
    INSDRIVER_EXPORT MessageInfo updatePipelineStepSupervisor(qint32 personId, QList<qint32> pipelineSteps) {
        INSCommonRequest<qint32, int, QList<qint32>> commonRequest(5114, personId, pipelineSteps);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    //批量修改pipeline step 的 coordinator
    INSDRIVER_EXPORT MessageInfo updatePipelineStepCoordinator(qint32 personId, QList<qint32> pipelineSteps) {
        INSCommonRequest<qint32, int, QList<qint32>> commonRequest(5115, personId, pipelineSteps);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }

    MessageInfo GetWorkflowDetailRequiredFiles(qint32 workflowStepId, QList<WorkFlowDetlFile> &detailFiles) {
        INSCommonRequest<QList<WorkFlowDetlFile>, qint32> commonRequest(5523, workflowStepId);
        commonRequest.WaitForFinished();
        detailFiles = commonRequest.retData;
        return commonRequest.m_return_value;
    }

    MessageInfo UpdateWorkflowDetailRequiredFiles(qint32 workflowStepId, QList<WorkFlowDetlFile> &detailFiles) {
        INSCommonRequest<qint32, qint32, QList<WorkFlowDetlFile>> commonRequest(5524, workflowStepId, detailFiles);
        commonRequest.WaitForFinished();
        return commonRequest.m_return_value;
    }
};
