#include "insdriverworkflowinterface.h"

#include "inscommonhandle.h"

namespace INS_INTERFACE {
    INSDRIVER_EXPORT MessageInfo CreateWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
        INSCommonRequest<INQWorkFlowVO> commonRequest(5515, workFlowVO);
        commonRequest.WaitForFinished();
        workFlowVO = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo GetWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
        INSCommonRequest<INQWorkFlowVO> commonRequest(5516, workFlowVO.workFlowId);
        commonRequest.WaitForFinished();
        workFlowVO = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //获取workFlow列表 pipelineType为1表示asset，2表示shot，3表示sequence
    INSDRIVER_EXPORT MessageInfo
    GetWorkFlowTempls(QList<INQWorkFlowVO> &workFlowVOs, qint32 projectId, qint32 pipelineType) {
        INSCommonRequest<QList<INQWorkFlowVO>> commonRequest(5517, projectId, pipelineType);
        commonRequest.WaitForFinished(-1);
        workFlowVOs = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //更新work-flow,id不为空,name不为空
    INSDRIVER_EXPORT MessageInfo UpdateWorkFlowTempl(INQWorkFlowVO &workFlowVO) {
        INSCommonRequest<INQWorkFlowVO> commonRequest(5518, workFlowVO);
        commonRequest.WaitForFinished();
        workFlowVO = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //删除work-flow,id不为空
    INSDRIVER_EXPORT MessageInfo DeleteWorkFlowTempl(qint32 workFlowId) {
        INSCommonRequest<qint32> commonRequest(5519, workFlowId);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    INSDRIVER_EXPORT MessageInfo CreatePrivateUseWorkFlow(INQWorkFlowVO &workFlowVO, qint32 workFlowId) {
        INSCommonRequest<INQWorkFlowVO> commonRequest(5520, workFlowId);
        commonRequest.WaitForFinished();
        workFlowVO = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

//    INSDRIVER_EXPORT MessageInfo GetWorkFlowInstance(INQWorkFlowVO &workFlowVO) {
//        //INSCommonRequest<INQWorkFlowVO> commonRequest(5521, workFlowVO.workFlowId);
//        //template <qint32 successCode, typename Recv, typename... Args>
//        INSCommonRequest<INQWorkFlowVO> commonRequest(5521, workFlowVO);
//        commonRequest.WaitForFinished();
//        workFlowVO = commonRequest.getRecvData();
//        return commonRequest.getRetValue();
//    }

    INSDRIVER_EXPORT MessageInfo GetWorkFlowInstance(TaskWorkflow& taskWorkflow, qint32 objectID, qint32 objectType)
    {
        INSCommonRequest<TaskWorkflow> commonRequest(5521, objectID, objectType);
        commonRequest.WaitForFinished();
        taskWorkflow = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //更新work-flow,id不为空,name不为空
    INSDRIVER_EXPORT MessageInfo UpdateWorkFlowInstance(TaskWorkflow & taskWorkflow) {
        INSCommonRequest<TaskWorkflow> commonRequest(5522, taskWorkflow);
        commonRequest.WaitForFinished();
        taskWorkflow = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    //创建pipeline step:name和type不能为空,type为1表示shot
    INSDRIVER_EXPORT MessageInfo CreatePipelineStep(INPipelineStep &pipelineStep) {
        INSCommonRequest<INPipelineStep> commonRequest(5110, pipelineStep);
        commonRequest.WaitForFinished();
        pipelineStep = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }
    //更新pipeline step:name和id不能为空
    INSDRIVER_EXPORT MessageInfo UpdatePipelineStep(INPipelineStep &pipelineStep) {
        INSCommonRequest<INPipelineStep> commonRequest(5111, pipelineStep);
        commonRequest.WaitForFinished();
        pipelineStep = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }
    //根据type获取pipeline step: 若type==0,表示获取全部, type==1表示获取asset,type==2表示获取shot
    INSDRIVER_EXPORT MessageInfo
    GetPipelineSteps(QList<INPipelineStep> &pipelineSteps, qint32 pipelineType, qint32 projectId) {
        INSCommonRequest<QList<INPipelineStep>> commonRequest(5112, pipelineType, projectId);
        commonRequest.WaitForFinished();
        pipelineSteps = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }
    //删除pipeline step:id不能为空
    INSDRIVER_EXPORT MessageInfo DeletePipelineStep(qint32 pipelineId) {
        INSCommonRequest<qint32> commonRequest(5113, pipelineId);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    //批量修改pipeline step 的 surpervisor
    INSDRIVER_EXPORT MessageInfo updatePipelineStepSupervisor(qint32 personId, QList<qint32> pipelineSteps) {
        INSCommonRequest<qint32> commonRequest(5114, personId, pipelineSteps);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    //批量修改pipeline step 的 coordinator
    INSDRIVER_EXPORT MessageInfo updatePipelineStepCoordinator(qint32 personId, QList<qint32> pipelineSteps) {
        INSCommonRequest<qint32> commonRequest(5115, personId, pipelineSteps);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    MessageInfo InstanceTaskByPipelineStep(qint32& taskId, const InstanceTaskRequest &detailFiles) {
        INSCommonRequest<qint32> commonRequest(5523, detailFiles);
        commonRequest.WaitForFinished();
        taskId = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    MessageInfo UpdateWorkflowDetailRequiredFiles(qint32 workflowStepId, QList<WorkFlowDetlFile> &detailFiles) {
        INSCommonRequest<qint32> commonRequest(5524, workflowStepId, detailFiles);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }

    MessageInfo ExportPipelineStep(qint32 sourceProjectId, PipelineStepExport& pipelineStepExport) {
        INSCommonRequest<PipelineStepExport> commonRequest(5116, sourceProjectId);
        commonRequest.WaitForFinished();
        pipelineStepExport = commonRequest.getRecvData();
        return commonRequest.getRetValue();
    }

    MessageInfo ImportPipelineStep(qint32 targetProjectId, const PipelineStepExport& pipelineStepExport) {
        INSCommonRequest<qint32> commonRequest(5117, targetProjectId, pipelineStepExport);
        commonRequest.WaitForFinished();
        return commonRequest.getRetValue();
    }
};
