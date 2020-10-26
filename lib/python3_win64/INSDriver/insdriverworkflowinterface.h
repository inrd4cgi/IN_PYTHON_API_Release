#pragma once


#include "insdatastructure.h"
#include "insdriver_global.h"


namespace INS_INTERFACE
{

	//创建work-flow,name不为空
	INSDRIVER_EXPORT INQRespondInfo CreateWorkFlowTempl(INQWorkFlowVO& workFlowVO);

	//获取workflow,id不为空
	INSDRIVER_EXPORT INQRespondInfo GetWorkFlowTempl(INQWorkFlowVO& workFlowVO);

	//获取workFlow列表，0表示该项条件不参与过滤
	INSDRIVER_EXPORT INQRespondInfo GetWorkFlowTempls(QList<INQWorkFlowVO>& workFlowVOs, qint32 projectId, qint32 pipelineType);

	//更新work-flow,id不为空,name不为空
	INSDRIVER_EXPORT INQRespondInfo UpdateWorkFlowTempl(INQWorkFlowVO& workFlowVO);

	//删除work-flow,id不为空
	INSDRIVER_EXPORT INQRespondInfo DeleteWorkFlowTempl(qint32 workFlowId);

	//通过workFlowId创建work-flow专属于某个asset或者shot的workFlow,返回全新的workFlow
	INSDRIVER_EXPORT INQRespondInfo CreatePrivateUseWorkFlow(INQWorkFlowVO& workFlowVO, qint32 workFlowId);

	//获取workflow的实例
	INSDRIVER_EXPORT INQRespondInfo GetWorkFlowInstance(INQWorkFlowVO& workFlowVO);

	INSDRIVER_EXPORT INQRespondInfo UpdateWorkFlowInstance(INQWorkFlowVO &workFlowVO);

	//创建pipeline step:name和type不能为空,type为1表示shot
	INSDRIVER_EXPORT INQRespondInfo CreatePipelineStep(INPipelineStep& pipelineStep, QVector<INWorkPath> &workPath);

	//更新pipeline step:name和id不能为空
	INSDRIVER_EXPORT INQRespondInfo UpdatePipelineStep(INPipelineStep& pipelineStep, QVector<INWorkPath> &workPath);

	//根据type获取pipeline step: 若type==0,表示获取全部, type==1表示获取asset,type==2表示获取shot
	//projectId=0表示获取全部,projectId=-1表示获取全局的pipelineStep,project!=0表示获取特定的
	INSDRIVER_EXPORT INQRespondInfo GetPipelineSteps(QList<INPipelineStep>& pipelineSteps, qint32 pipelineType = 0, qint32 projectId = 0);

	//删除pipeline step:id不能为空
	INSDRIVER_EXPORT INQRespondInfo DeletePipelineStep(qint32 pipelineId);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief updatePipelineStepSupervisor 批量修改PipelineStep的Supervisor
	 * \param personId Supervisor人员ID,必填。
	 * \param pipelineStep 被修改的PipelineStep ID 列表
	 * \return 业务操作结果
	 */
	INSDRIVER_EXPORT INQRespondInfo updatePipelineStepSupervisor(qint32 personId, QList<qint32> pipelineSteps);

	/*!
	 * \ingroup businessAPI_fileModule
	 * \brief updatePipelineStepCoordinator 批量修改PipelineStep的Coordinator
	 * \param personId Coordinator人员ID,必填。
	 * \param pipelineStep 被修改的PipelineStep ID 列表
	 * \return 业务操作结果
	 */
	INSDRIVER_EXPORT INQRespondInfo updatePipelineStepCoordinator(qint32 personId, QList<qint32> pipelineSteps);

    /*!
     * \brief GetPipelineStepWorkPath 根据PipelineStepTemplate的ID，获取此PipelineStep下的输出文件路径列表
     * \param pipelineId
     * \param workPath
     * \return
     */
    INSDRIVER_EXPORT INQRespondInfo GetPipelineStepWorkPath(qint32 pipelineId, QVector<INWorkPath> &workPath);


	INSDRIVER_EXPORT INQRespondInfo GetWorkflowDetailRequiredFiles(qint32 workflowStepId, QList<WorkFlowDetlFile>& detailFiles);

	INSDRIVER_EXPORT INQRespondInfo UpdateWorkflowDetailRequiredFiles(qint32 workflowStepId, QList<WorkFlowDetlFile>& detailFiles);
};