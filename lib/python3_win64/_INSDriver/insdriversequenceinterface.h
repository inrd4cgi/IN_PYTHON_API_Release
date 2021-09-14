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

    /*!
     * \brief GetSequenceShotGroup
     * \param shotGroup
     * \param shotGroupId
     * \param shotGroupVersion 若版本号为缺省值，则服务器返回shotGroupId默认最新的版本
     * \return
     */
    INSDRIVER_EXPORT MessageInfo GetSequenceShotGroup(INSequenceShotGroup &shotGroup, qint32 shotGroupId, qint32 shotGroupVersion = 0);

    INSDRIVER_EXPORT MessageInfo CreateSequenceshotGroup(INSequenceShotGroup& shotGroup);

    INSDRIVER_EXPORT MessageInfo EditSequenceshotGroup(INSequenceShotGroup& shotGroup);

    INSDRIVER_EXPORT MessageInfo DeleteSequenceShotGroup(qint32 shotGroupId);

    INSDRIVER_EXPORT MessageInfo EditSequenceShotFileList(QList<INSequenceShotFile>& shotFiles, qint32 shotGroupId);

    INSDRIVER_EXPORT MessageInfo GetSequenceShotGroupsFromRecycleBinOfShotFile(QList<INSequenceShotFileRecycle>& shotGroups, qint32 shotGroupId);

    INSDRIVER_EXPORT MessageInfo GetSequenceShotGroupVersionList(QList<INSequenceShotGroup>& shotGroups, qint32 shotGroupId);


    INSDRIVER_EXPORT MessageInfo SaveShotFilesReviewDataOfSequenceShotGroup(const INSequenceShotGroupReview& reviewData);

    INSDRIVER_EXPORT MessageInfo GetShotGroupGeneralShotsInformation(qint32 shotGroupId,INSequenceShotStatus & shotStatus);
};
