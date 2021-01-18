//
// Created by 10769 on 12/2/2020.
//

#pragma once

#include "insdatastructure.h"
#include "insdriver_global.h"

namespace INS_INTERFACE
{
    INSDRIVER_EXPORT MessageInfo GetSequencerList(QList<INSequence>& sequencerList, const SequenceFilterParam& filterParam);

    INSDRIVER_EXPORT MessageInfo CreateSequencer(INSequence& sequencer, const QList<TagParam>& tagParam);

    INSDRIVER_EXPORT MessageInfo EditSequencer(INSequence& sequencer);

    INSDRIVER_EXPORT MessageInfo DeleteSequencer(qint32 sequencerId);

    INSDRIVER_EXPORT MessageInfo GetSequenceShotGroups(QList<INSequenceShotGroup> &shotGroups, qint32 taskId);

    INSDRIVER_EXPORT MessageInfo GetSequenceShotGroup(INSequenceShotGroup &shotGroup, qint32 shotGroupId);

    INSDRIVER_EXPORT MessageInfo CreateSequenceshotGroup(INSequenceShotGroup& shotGroup);

    INSDRIVER_EXPORT MessageInfo EditSequenceshotGroup(INSequenceShotGroup& shotGroup);

    INSDRIVER_EXPORT MessageInfo DeleteSequenceShotGroup(qint32 shotGroupId);

    INSDRIVER_EXPORT MessageInfo EditSequenceShotFileList(QList<INSequenceShotFile>& shotFiles, qint32 shotGroupId);

    INSDRIVER_EXPORT MessageInfo GetSequenceShotGroupsFromRecycleBinOfShotFile(QList<INSequenceShotFileRecycle>& shotGroups, qint32 shotGroupId);

    INSDRIVER_EXPORT MessageInfo GetSequenceShotGroupVersionList(QList<INSequenceShotGroup>& shotGroups, qint32 shotGroupId);

    INSDRIVER_EXPORT MessageInfo RestoreSequenceShotGroupToCurrentVersion(INSequenceShotGroup& shotGroup, qint32 shotGroupId, qint32 version);

    INSDRIVER_EXPORT MessageInfo SaveShotFilesReviewDataOfSequenceShotGroup(const INSequenceShotGroupReview& reviewData);
};