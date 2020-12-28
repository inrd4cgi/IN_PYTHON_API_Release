//
// Created by 10769 on 12/2/2020.
//

#include "insdriversequenceinterface.h"
#include "inscommonhandle.h"

namespace INS_INTERFACE
{
    MessageInfo GetSequencerList(QList<INSequence> &sequencerList, const SequenceFilterParam &filterParam)
    {
        INSCommonRequest<QList<INSequence>, SequenceFilterParam> commonRequest(5400, filterParam);
        WAITFORFINISHEDANDGETVALUETHENRETURN(sequencerList)
    }

    MessageInfo CreateSequencer(INSequence &sequencer, const QList<TagParam> &tagParam)
    {
        INSCommonRequest<INSequence, INSequence, QList<TagParam>> commonRequest(5401, sequencer, tagParam);
        WAITFORFINISHEDANDGETVALUETHENRETURN(sequencer)
    }

    MessageInfo EditSequencer(INSequence &sequencer)
    {
        INSCommonRequest<INSequence, INSequence> commonRequest(5402, sequencer);
        WAITFORFINISHEDANDGETVALUETHENRETURN(sequencer)
    }

    MessageInfo DeleteSequencer(qint32 sequencerId)
    {
        INSCommonRequest<qint32, qint32> commonRequest(5403, sequencerId);
        WAITFORFINISHEDTHENRETURN
    }

    MessageInfo GetSequenceShotGroups(QList<INSequenceShotGroup> &shotGroups, qint32 taskId)
    {
        INSCommonRequest<QList<INSequenceShotGroup>, int> commonRequest(5404, taskId);
        WAITFORFINISHEDANDGETVALUETHENRETURN(shotGroups)
    }

    MessageInfo GetSequenceShotGroup(INSequenceShotGroup &shotGroup, qint32 shotGroupId)
    {
        INSCommonRequest<INSequenceShotGroup, int> commonRequest(5405, shotGroupId);
        WAITFORFINISHEDANDGETVALUETHENRETURN(shotGroup)
    }

    MessageInfo CreateSequenceshotGroup(INSequenceShotGroup &shotGroup)
    {
        INSCommonRequest<INSequenceShotGroup, INSequenceShotGroup> commonRequest(5406, shotGroup);
        WAITFORFINISHEDANDGETVALUETHENRETURN(shotGroup)
    }

    MessageInfo EditSequenceshotGroup(INSequenceShotGroup &shotGroup)
    {
        INSCommonRequest<INSequenceShotGroup, INSequenceShotGroup> commonRequest(5407, shotGroup);
        WAITFORFINISHEDANDGETVALUETHENRETURN(shotGroup)
    }

    MessageInfo DeleteSequenceShotGroup(qint32 shotGroupId)
    {
        INSCommonRequest<qint32, qint32> commonRequest(5408, shotGroupId);
        WAITFORFINISHEDTHENRETURN
    }

    MessageInfo EditSequenceShotFileList(QList<INSequenceShotFile> &shotFiles, qint32 shotGroupId)
    {
        INSCommonRequest<QList<INSequenceShotFile>, qint32, QList<INSequenceShotFile>> commonRequest(5409, shotGroupId, shotFiles);
        WAITFORFINISHEDANDGETVALUETHENRETURN(shotFiles)
    }

    MessageInfo GetSequenceShotGroupsFromRecycleBinOfShotFile(QList<INSequenceShotFileRecycle> &shotGroups, qint32 shotGroupId)
    {
        INSCommonRequest<QList<INSequenceShotFileRecycle>, qint32> commonRequest(5410, shotGroupId);
        WAITFORFINISHEDANDGETVALUETHENRETURN(shotGroups)
    }

    MessageInfo GetSequenceShotGroupVersionList(QList<INSequenceShotGroup> &shotGroups, qint32 shotGroupId)
    {
        INSCommonRequest<QList<INSequenceShotGroup>, qint32> commonRequest(5411, shotGroupId);
        WAITFORFINISHEDANDGETVALUETHENRETURN(shotGroups)
    }

    MessageInfo RestoreSequenceShotGroupToCurrentVersion(INSequenceShotGroup &shotGroup, qint32 shotGroupId, qint32 version)
    {
        INSCommonRequest<INSequenceShotGroup, qint32, qint32 > commonRequest(5412, shotGroupId, version);
        WAITFORFINISHEDANDGETVALUETHENRETURN(shotGroup)
    }

    MessageInfo SaveShotFilesReviewDataOfSequenceShotGroup(const INSequenceShotGroupReview &reviewData)
    {
        INSCommonRequest<qint32, INSequenceShotGroupReview> commonRequest(5413, reviewData);
        WAITFORFINISHEDTHENRETURN
    }
}