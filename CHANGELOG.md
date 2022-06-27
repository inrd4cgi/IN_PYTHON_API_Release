# Change Log

All notable changes to this project will be documented in this file.

## [1.50.3] - 2022-06-27
### Fixed
  * Fix `editTaskOutputFile`

## [1.50.2] - 2022-04-25
### Rebuild
  * 

## [1.50.1] - 2022-04-25
### Rebuild
  * 

## [1.50.0] - 2022-04-25
### Added
  * Add `editPipelineScore`, `getPipelineScore`

## [1.49.2] - 2022-04-18
### Fixed
  * Fix `createPipeline`

## [1.49.1] - 2022-04-14
### Rebuild
  * 

## [1.49.0] - 2022-04-14
### Added
  * Add `modifyPersonPermissionTemp`

## [1.48.3] - 2022-04-14
### Fixed
  * Fix `createWorkFlowTempl`

## [1.48.2] - 2022-04-13
### Rebuild
  * Add Variable for `INPipelineSimple`

## [1.48.1] - 2022-04-13
### Rebuild
  * 

## [1.48.0] - 2022-04-12
### Updated
  * `createPipeline`, `updatePipeline`, `getPipelineStep`, `getPipelineSteps` 

## [1.47.2] - 2022-03-31
### Fixed
  * Fix `getTasksByConditions` 

## [1.47.1] - 2022-03-31
### Fixed
  * Fix `getTasksByConditions` 

## [1.47.0] - 2022-03-31
### Added
  * Add function `getTaskAssigneeScoreHistory` 


## [1.46.0] - 2022-03-14
### Modified
  * Add argument `project_id` for function `makeTag`, `removeTag` 


## [1.45.0] - 2022年3月10日18:15:39

### Added

* xlwt

## [1.44.0] - 2022年3月10日16:35:22

### Added

* json_tools

## [1.43.0] -2022年3月10日16:35:20

### Added

* PIL

## [1.42.0] - 2022-02-24

### Fixed

* Fix `data_flow_get_task_list`

## [1.41.0] - 2022-02-24

### Added

* Add `getPipelineStepMatchedGroupByProjectId`

## [1.40.0] - 2022-02-23

### Rebuild

## [1.39.0] - 2022-02-23

### Added

* `editTaskOutputFile` add `is_review`

## [1.38.0] - 2022年2月23日12:00:57

### Fixed

* Fix `data_flow_get_task_list`

## [1.37.0] - 2022-01-10

### Added

* Add `approveTaskApprovalStatus`

## [1.36.0] - 2021-12-29

### Added

* Add `getPermissionTemps`

## [1.35.3] - 2021-12-29

### Fixed

* Fix `getProject`error

## [1.35.2] - 2021-12-27

### Fixed

* Fix `IN_RUN_SERVER.py`

## [1.35.1] - 2021-12-27

### Fixed

* Modify `IN_RUN_SERVER.py`

## [1.35.0] - 2021-12-23

### Added

* Add "tag_name_reg_exp" for `getAssetsByCondition`

## [1.34.0] - 2021-12-22

### Added

* Add `uploadFilesBatch`

## [1.33.0] - 2021-12-20

### Added

* Add `getTasksOutputFiles`

## [1.32.3] - 2021-12-16

### Fixed

* Fix `getTasksByConditions` parameter "tags_name" to "tag_name_reg_exp"

## [1.32.2] - 2021-12-15

### Fixed

* Parse `uploadFootageId` failed

## [1.32.1] - 2021-12-14

### Fixed

* Fix `getPersonList` return incorrect values.

## [1.32.0] - 2021-12-09

### Added

* Add parameter "file_name" for `uploadOutputFile`.

## [1.31.0] - 2021-12-09

### Added

* Add parameter "directory" for `uploadOutputFile`.
* Add return value "pid" for `start_server`.

## [1.30.2] - 2021-12-06

### Fixed

* fix login: add token and url.

## [1.30.1] - 2021-12-06

### Fixed

* fix download: while file size is 0 bit.

## [1.30.0] - 2021-12-01

### Updated

* update `login`

## [1.29.0] - 2021-11-24

### Added

* Add `addPersonToProject`

## [1.28.0] - 2021-11-24

### Added

* Add `getSceneListPro`

## [1.27.7] - 2021-11-23

### Fixed

* Fixed `deleteProject` service ID

## [1.27.6] - 2021-11-08

### Added

* Add function `getPipelineStep`

## [1.27.5] - 2021-10-28

### Rebuild

## [1.27.4] - 2021-10-28

### Added

* Add traceback for start_server

## [1.27.3] - 2021-10-27

### Rebuild

## [1.27.2] - 2021-10-20

### Fixed

* Update interface `getTaskRelatedFiles`, Add Attribute `isRecursion` for FileVO

## [1.27.1] - 2021-10-20

### Fixed

* Update interface `getTaskRelatedFiles`, Add Attribute `isRecursion` for FileVO

## [1.27.0] - 2021-9-16

### Added

* Add new custom interface `getTasksNextAvailableStatus`

## [1.26.0] - 2021-9-14

### Added

* Add new interface `getRequiredFiles`

## [1.25.6] - 2021-9-13

### Fixed

* Fix checkin failed

## [1.25.5] - 2021-9-10

### Fixed

* Fix incorrect Data Structure

## [1.25.4] - 2021-9-10

### Rebuild

## [1.25.3] - 2021-9-10

### Rebuild

## [1.25.2] - 2021-9-10

### Rebuild

## [1.25.1] - 2021-9-10

### Fixed

* try to fix start_server failed

## [1.25.0] - 2021-9-10

### Added

* add `decryptPassword` method

## [1.24.1] - 2021-9-10

### Fixed

* Download failed

## [1.24.0] - 2021-9-6

### Added

* Update API

### Fixed

* Cancel Singleton
* Download failed while folder exists

## [1.23.3] - 2021-7-22

### Rebuild

## [1.23.2] - 2021-7-22

### Rebuild

## [1.23.1] - 2021-7-22

### Rebuild

## [1.23.0] - 2021-7-22

### Added

* Support javascript

## [1.22.0] - 2021-7-16

### Added

* Enhance error message

## [1.21.0] - 2021-7-16

### Added

* check md5 before `download`

## [1.20.0] - 2021-7-8

### Added

* add `findTaskStatus` method

## [1.19.0] - 2021-7-8

### Added

* Modify Exception message
* Modify README.md

## [1.18.13] - 2021-6-26

### Fixed

* Fix the attribute `tags` of `INAsset` got incorrect value

## [1.18.12] - 2021-6-21

### Added

* Added a func `get_logged_status` to validate the login status

## [1.18.11] - 2021-6-21

### Fixed

* Fixed a bug that caused files to not upload correctly

## [1.18.10.1] - 2021-5-18

### Fixed

* rebuild

## [1.18.10.0] - 2021-5-18

### Fixed

* Fix `getTasksByCondition` in backend

### Added

* Add `TaskPipelineType` for distinguish `PipelineType` and `TaskPipelineType`

## [1.18.9.0] - 2021-5-12

### Fixed

* Fix `deleteAsset`

## [1.18.8.1] - 2021-5-12

### Fixed

* rebuild

## [1.18.8.0] - 2021-5-12

### Fixed

* `getShotsByCondition` add argument `task_filter_param```
* `getAssetsByCondition` add argument `task_filter_param```

## [1.18.7.0] - 2021-5-11

### Fixed

* pops up error while checkin

## [1.18.6.0] - 2021-4-21

### Updated

* `data_flow_get_task_list` https://wsrd.atlassian.net/browse/CP-169

## [1.18.5.0] - 2021-4-19

### Add test files

## [1.18.4.0] - 2021-4-19

### Add test files

## [1.18.3.0] - 2021-4-19

### Rebuild

## [1.18.2.0] - 2021-4-19

### Rebuild

## [1.18.1.0] - 2021-4-19

### Updated

* `data_flow_get_task_list`

## [1.18.0.0] - 2021-4-1

### Updated

* Update Structure
  ```
  New Structures:
  [
      'ExtraFilter'    # 筛选的额外条件
  ]

  -------------------- Structure INTask --------------------
  New Attributes:
  [
      'lastModifyTime'
  ]

  -------------------- Structure TaskFilterParam --------------------
  New Attributes:
  [
      'excludeDeletedItem', 
      'extraFilter', 
      'tagNameRegExp'
  ]

  -------------------- Structure TaskWorkflowDetail --------------------
  New Attributes:
  [
      'alias', 
  ]

  ```

## [1.17.2.0] - 2021-4-1

### Updated

* remove logging log.txt log file output
* `data_flow_save_task` make a sequence version whatever successfully uploaded

## [1.17.1.0] - 2021-4-1

### Updated

* remove MD5 checked for IN_API_CLIENT_B download

## [1.17.0.0] - 2021-3-10

### Updated

* python3_api updated, new interface for notification user logged status

## [1.16.3.0] - 2021-3-4

### Updated

* `data_flow_update_all_task_files` using cover_inter_and_out argument to control the intermediate file and output file covered needed status
* 

## [1.16.2.0] - 2021-3-4

### Updated

* `data_flow_get_task_list` merge audit task

## [1.16.1.0] - 2021-3-4

### Fixed

* `data_flow_get_task_list` ignore sequence task

## [1.16.0.0] - 2021-3-2

### Updated

* `data_flow_get_task_list` using batch-operation

## [1.15.4.0] - 2021-3-1

### Fixed

* data_flow_get_task_list get tasks with types

## [1.15.3.0] - 2021-2-24

### Updated

* data_flow_get_task_list optimize

## [1.15.2.0] - 2021-2-22

### Updated

* less message print

## [1.15.1.0] - 2021-2-22

### Updated

* less message print
* data_flow_get_task_list optimize

## [1.15.0.0] - 2021-2-17

### Updated

* `data_flow_get_task_list`

### Note

* Not compatible with LoaderV1.13.x.x version, compatible with LoaderV1.14.x.x

## [1.14.0.0] - 2021-2-2

### Fixed

* Fix `start_server` failed in `Katana`

## [1.13.4.0] - 2021-1-29

### Updated

* call_api_request return `[{}, {}]` if none result of INI.jsonRequest

## [1.13.3.0] - 2021-1-26

### Fixed

* Turn off Flask logger while using `IN_API_SERVER_B` to Run Server

## [1.13.2.0] - 2021-1-25

### Fixed

* Intermediate file data returned

## [1.13.1.0] - 2021-1-21

### Updated

* try catch os.makedirs

## [1.13.0.0] - 2021-1-20

### Updated

* update `update deleteRecycleBin`

## [1.12.0.0] - 2021-1-19

### Updated

* update `test_in_api_client`

## [1.11.0.0] - 2021-1-18

### Updated

* Update Structure

```
    -------------------- Structure AssetFilterParam --------------------
    New Attributes:
    ['tagSearchAndOr']
  
    -------------------- Structure FileVO --------------------
    New Attributes:
    ['checkoutBy', 'checkoutTime', 'isIntermediate', 'isReview', 'lastModifiedBy']
  
    -------------------- Structure INQGetPrjBusinessFilter --------------------
    New Attributes:
    ['isDeleted']
  
    -------------------- Structure INQWorkPath --------------------
    New Attributes:
    ['isIntermediate', 'isReview']
  
    -------------------- Structure INTask --------------------
    New Attributes:
    ['toValidate', 'validationScript', 'loaderScript', 'scene']
  
    -------------------- Structure INTaskComment --------------------
    New Attributes:
    ['isApprover', 'statusDate', 'taskStatus']
  
    -------------------- Structure ProjectTaskInfo --------------------
    New Attributes:
    [   'leftDay',
        'newlyTaskCount',
        'personTaskInfoMap',
        'projectDueTime',
        'projectId',
        'projectIssueTime',
        'projectName',
        'taskStatusInfoMap',
        'teamInfoMap',
        'totalTaskCount']
    Deprecated Attributes:
    ['currproject', 'newlytasks', 'persontotasklist', 'taskList', 'teamtotasklist']
  
    -------------------- Structure ShotFilterParam --------------------
    New Attributes:
    ['tagSearchAndOr']
  
    -------------------- Structure TaskFileRelationEditParam --------------------
    New Attributes:
    ['isIntermediate', 'isReview']
    Deprecated Attributes:
    ['isIntermediateFile']

```

## [1.10.2.0] - 2021-1-18

### Fixed

* build script

## [1.10.1.3] - 2021-1-18

### Fixed

* Rebuild

## [1.10.1.2] - 2021-1-18

### Fixed

* Rebuild

## [1.10.1.1] - 2021-1-18

### Fixed

* Rebuild

## [1.10.1.0] - 2021-1-15

### Updated

* try makrdirs method in data_flow_get_task_files_record

## [1.10.0.0] - 2021-1-15

### Updated

* Update the latest of IN Python API

## [1.9.1.0] - 2021-1-18

### Updated

* `data_flow_get_task_list` return data

## [1.9.0.0] - 2021-1-18

### Added

* new interface for L&P `get_audit_tasks`

## [1.8.5.0] - 2021-1-17

### Updated

* `data_flow_get_task_list` return data

## [1.8.4.0] - 2021-1-17

### Updated

* `data_flow_get_task_list` return data

## [1.8.3.0] - 2021-1-17

### Rebuild

## [1.8.2.0] - 2021-1-17

### Updated

* `data_flow_get_task_list` return data

## [1.8.1.2] - 2021-1-15

### Fixed

* Comment out logging

## [1.8.1.1] - 2021-1-15

### Fixed

* Fix `updatePipeline` invalid param

## [1.8.1.0] - 2021-1-15

### Updated

* data_flow_update_all_task_files, reordered the order of download, before [ref-req-int-out-don] now [ref-int-out-don-req]

## [1.8.0.0] - 2021-1-15

### Updated

* data_flow_change_task_status, skip download output file when it's already existed in the required file

## [1.7.0.4] - 2021-1-11

### Fixed

* Fix `RecycleBin` return code

## [1.7.0.3] - 2021-1-11

### Fixed

* Fix `getBusRecycleBinList` return code

## [1.7.0.2] - 2021-1-7

### Fixed

* Fix connectToServer port Type

## [1.7.0.1] - 2021-1-7

### Fixed

* Fix Server port

## [1.7.0.0] - 2021-1-7

### Updated

* Add Method `updatePipelineStep, updateWorkFlowTempl`

## [1.6.0.0] - 2021-1-5

### Updated

* Add Method `updatePipelineStep`

## [1.5.0.1] - 2021-1-5

### Fixed

* Fix `connectToServer`

## [1.5.0.0] - 2020-12-28

### Updated

* Add Methods
  ```
  createTask
  superSearch
  ```

## [1.4.0.4] - 2020-12-28

### Updated

* build script

## [1.4.0.3] - 2020-12-28

### Updated

* config.json

## [1.4.0.2] - 2020-12-28

* Rebuild

## [1.4.0.1] - 2020-12-28

### Updated

* README.md

## [1.4.0.0] - 2020-12-24

### Updated

* Add Methods
  ```
  createProject
  createPipelineStep
  createWorkFlowTempl
  ```

## [1.3.1.0] - 2020-12-24

### Fixed

* Fix
* **IN_PYTHON_API_FUNC** [`getVariantByAssetId`]

## [1.3.0.0] - 2020-12-24

### Updated

* Use the mapping path following the project

## [1.2.23.3] - 2020-12-18

### Updated

* **IN_PYTHON_API** [`data_flow_change_task_status`]
* message optimize

## [1.2.23.2] - 2020-12-16

### Fixed

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * repath from assets to asset

## [1.2.23.1] - 2020-12-15

### Updated

* **IN_PYTHON_API** [`data_flow_get_task_files_record`]
  * doesn't call IN_API if the task id is invalid

## [1.2.23.0] - 2020-12-12

### Added

* **IN_DATA_STRUCTURE.py**
  * Add Structure `SearchTagParam`
  * Modify Attributes
    ```
    AssetFilterParam
        New Attributes:
        ['tagNames']

    FileTransferInfo
        New Attributes:
        ['transferRecordId']

    INQProjectVO
        New Attributes:
        ['rootDir']

    INQWorkFlowDetail
        New Attributes:
        ['alias']

    INShot
        New Attributes:
        ['projectType']

    INTask
        New Attributes:
        ['objectAlias', 'alias']

    SearchTagParam
        New Attributes:
        ['objectIds', 'projectId', 'sceneIds']

    TaskFilterParam
        New Attributes:
        ['alias', 'types']
        Deprecated Attributes:
        ['type']
    ```

### Modified

* **IN_API_CLIENT_B.py** [`getBusRecycleBinList`]
  * add argument "project_id"

## [1.2.22.0] - 2020-12-11

### Update

* Update Python API 1211

## [1.2.21.3] - 2020-12-11

### Updated

* rebuild

## [1.2.21.2] - 2020-12-11

### Updated

* **IN_PYTHON_API** [`data_flow_add_file2output_file`]
  * Using `upload_files` interface by default

## [1.2.21.1] - 2020-12-10

### Fixed

* **IN_API_CLIENT_B** [`checkin`]
  * Fix file handle

## [1.2.21.0] - 2020-12-10

### Fixed

* **IN_PYTHON_API** [`data_flow_add_file2output_file`]
  * use in_api_client interface to add a file to task output

## [1.2.20.0] - 2020-12-8

### Updated

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * Supported customize output directory for task

## [1.2.19.0] - 2020-12-7

### Updated

* **IN_PYTHON_API** [`data_flow_get_task_list`]
  * return `type`

## [1.2.18.1] - 2020-12-4

### Updated

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * save_task when task status from WIP->Any or Any->WIP

## [1.2.18.0] - 2020-12-1

### Updated

* Split `IN_PYTHON_CLIENT.py` `IN_PYTHON_SERVER.py` To `IN_PYTHON_CLIENT_B.py`, `IN_PYTHON_SERVER_B.py`

## [1.2.17.2] - 2020-12-1

### Updated

* **IN_PYTHON_API** [`data_flow_get_task_list`]
  * return `project` and `pipelineStep`

## [1.2.17.1] - 2020-12-1

### Updated

* **IN_COMMON** [`get_map_path`]
  * function updated

## [1.2.17.0] - 2020-11-27

### Fixed

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * Correctly subtract the uploaded files

## [1.2.16.0] - 2020-11-27

### Fixed

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * upload all files of directory of task output when change the task status from Working-In-Progress to Pending-Approval

## [1.2.15.1] - 2020-11-23

### Updated

* **IN_API_CLIENT** [`createAsset`]
  * add new argument "alias"

## [1.2.15.0] - 2020-11-26

### Updated

* **IN_PYTHON_API** [`data_flow_add_file2output_file`]
  * new added `pre_check` parameter, check the file if already uploaded, the file will be ignored if already uploaded
* **IN_PYTHON_API** [`data_flow_get_task_files_record`]
  * new added directory data for output files

## [1.2.14.4] - 2020-11-25

### Updated

* **IN_PYTHON_API** [`data_flow_get_task_files_record`]
  * If there is a directory in the output file, create it

## [1.2.14.3] - 2020-11-25

### Updated

* **IN_PYTHON_API** [`data_flow_task_output_files`]
  * Change the format of data return from file-name to file-relative-path

## [1.2.14.2] - 2020-11-23

### Fixed

* **IN_PYTHON_API** [`data_flow_save_task`]
  * fixed the data for check-in and the locally-changed file should now be successfully uploaded
  * create sequence version after check-in

## [1.2.14.1] - 2020-11-23

### Updated

* **IN_COMMON** [`get_map_path`]
  * use python's module pathlib to get HOME directory
* ** README.md**
  * added How to `Change IN Server`

## [1.2.14] - 2020-11-23

### Fixed

* **IN_PYTHON_API** [`data_flow_update_all_task_files`]
  * Sequence files can now be downloaded correctly

## [1.2.13.4] - 2020-11-20

### Updated

* **IN_PYTHON_API** [`data_flow_get_task_files_record`]
  * method return from [required_file, intermediate_file, output_file] to (task_id, [required_file, intermediate_file, output_file])

## [1.2.13.3] - 2020-11-20

### Updated

* **IN_PYTHON_API** [`data_flow_task_output_files`]
  * Filter out intermediate files and folders

## [1.2.13.2] - 2020-11-20

### Updated

* **IN_API_CLIENT** [`api_call`]
  * set up false for customize_timeout by default

## [1.2.13.1] - 2020-11-18

### Fixed

* **IN_PYTHON_API** [`data_flow_save_task`]
  * Invalid output parameter

## [1.2.13] - 2020-11-18

### Updated

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * Create a sequence version when change the status of task from Working-In-Progress to Pending-Approval
* **IN_PYTHON_API** [`data_flow_save_task`]
  * Use internal interfaces to streamline data

## [1.2.12.1] - 2020-11-17

### Merged

## [1.2.12] - 2020-11-17

### Fixed

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * Update the sequence correctly to the latest version

### Added

* **IN_PYTHON_API** [`get_sequence_files`]
  * new interface

### Updated

* **IN_PYTHON_API** [`data_flow_update_all_task_files`]
  * Use the new interface

### Updated

* **IN_PYTHON_API** [`data_flow_update_task_sequence`]
  * Rewrite the

## [1.2.11] - 2020-11-17

### Fixed

* **IN_PYTHON_API** [`data_flow_update_all_task_files`]
  * The sequence of required of the task can be updated for a correct version

## [1.2.10] - 2020-11-13

### Fixed

* **IN_PYTHON_API** [`_download_file`]
  * modified from FileVO.version to FileVO.currentVersion

## [1.2.9.11] - 2020-11-13

### Fixed

* **IN_PYTHON_API** [`data_flow_save_task`]
  * Set sequence version correctly

## [1.2.9.10] - 2020-11-13

### Updated

* rebuild

## [1.2.9.9] - 2020-11-13

### Updated

* using cython 3.0a6

## [1.2.9.8] - 2020-11-13

### Updated

* rebuild

## [1.2.9.7] - 2020-11-13

### Updated

* **IN_PYTHON_API** [`INDownloadFileQWorker`]
  * _`deal_transit_signal` change message level from info to debug

## [1.2.9.6] - 2020-11-13

### Updated

* rebuild

## [1.2.9.5] - 2020-11-13

### Updated

* rebuild

## [1.2.9.4] - 2020-11-13

### Updated

* rebuild

## [1.2.9.3] - 2020-11-13

### Fixed

* **IN_PYTHON_API_FUNC**
  * shows approvalList, while using `getTasksByConditions`, `getPipelineSteps`

## [1.2.9.2] - 2020-11-13

### Fixed

* **IN_PYTHON_API**  [`data_flow_change_task_status`]
  * update the result of function return

## [1.2.9.1] - 2020-11-13

### Updated

* rebuild

## [1.2.9.0] - 2020-11-13

### Deprecated

* **createScene**
  * Use `createShot` instead

### Modified

* **createShot**
  * Add new argument, "season", "episode"

## [1.2.8.3] - 2020-11-13

### Fixed

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * Simplified message display

## [1.2.8.2] - 2020-11-13

### Fixed

* Extra Path problem fix

## [1.2.8.1] - 2020-11-13

### Updated

* rebuild

## [1.2.8] - 2020-11-13

### Fixed

* **IN_PYTHON_API** [`upload_file`]
  * Path problem fix

## [1.2.7.2] - 2020-11-12

### Fixed

* Stop all services before building to ensure successful build

## [1.2.7.1] - 2020-11-12

### Updated

* rebuild

## [1.2.7] - 2020-11-12

### Fixed

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * Fixed the problem of relative path

## [1.2.6.2] - 2020-11-12

### Updated

* **IN_COMMON**
  * Start info

## [1.2.6.1] - 2020-11-12

### Added

* python3 six module

## [1.2.6] - 2020-11-12

### Updated

* **src/script/run_api_server.bat.in** **API_TEMPLATES**
* The service start method

## [1.2.5.2] - 2020-11-12

### Updated

* **src/setup**
* py2pyd build scripts

## [1.2.5.1] - 2020-11-11

### Added

* **src/test/unittest_functional**

## [1.2.5] - 2020-11-11

### Added

* **IN_API_CLIENT**
  * Double-ended support with different python version

## [1.2.4] - 2020-11-11

### Updated

* **IN_PYTHON_API** [`data_flow_get_task_files_record`]
  * Sequence Create-Time display
* **IN_PYTHON_API**
  * convert all possibly exists the type of `unicode or bytes` to `str` by using `IN_COMMON.make_common_str`

## [1.2.3] - 2020-11-11

### Fixed

* **IN_PYTHON_API** [`download_file`]

## [1.2.2] - 2020-11-10

### Fixed

* **IN_PYTHON_API** [`data_flow_get_task_files_record`]
  * Sequence display correct

## [1.2.1.1] - 2020-11-10

### Fixed

* **src/IN_STREAMING.py**
  * use wrong oepn type in `os.open`

## [1.2.1.0] - 2020-11-10

### Added

* **src/IN_API_CLIENT.py**
  * Before return checkin result, Inspect file status after upload file successfully

## [1.2.0.4] - 2020-11-10

### Added

* **src/setup/setup_release.bat**
  * Python2 & Python3 Build

## [1.2.0.3] - 2020-11-10

### Updated

* **src/setup/** scripts

## [1.2.0.2] - 2020-11-10

### Added

* Some scripts for build the pyd of python3

## [1.2.0.1] - 2020-11-10

### Added

* **IN_COMMON** [`current_info`]
  * VERSION display

## [1.2.0] - 2020-11-10

### Updated

* **IN_PYTHON_API**
  * Service Preliminary Python3 Supported
  * Open it: `config.json: SERVICE_PYTHON_VERSION_3 = True`

## [1.1.4] - 2020-11-10

### Fixed

* **IN_PYTHON_API** [`data_flow_add_file2required_file`]
  * Unified as str type (python2) comparison

### Added

* **IN_PYTHON_API** [`data_flow_update_task_sequence`]
  * new interface

## [1.1.3] - 2020-11-9

### Renames

* **IN_API_CLIENT** [`prepare_server`]
  * rename `prepare_server` to `_prepare_server`, will call default when calling `start_serve`

## [1.1.2] - 2020-11-9

### Fixed

* **IN_PYTHON_API** [`data_flow_change_task_status`]

## [1.1.1.3] - 2020-11-9

### Updated

* **IN_PYTHON_API_Release**

## [1.1.1.2] - 2020-11-9

### Updated

* **test**

## [1.1.1.1] - 2020-11-9

### Updated

* **src/setup/setup_release.py**

## [1.1.1] - 2020-11-9

### Updated

* **src/setup/setup_release.py**
  * rollback

## [1.1.0] - 2020-11-9

### Release

## [1.1.0 pre-alpha-02] - 2020-11-9

### Updated

* **IN_PYTHON_API** [`data_flow_change_task_status`]

### Fixed

* **IN_PYTHON_API**
  * Chinese display problem

## [1.1.0 pre-alpha-01] - 2020-11-9

### Updated

* **lib.python2_win64** **lib.python3_win64**

### Updated

* **IN_PYTHON_API._auto_gen**
  * Json serialization

## [1.0.16] - 2020-11-8

### Added

* **IN_DATA_STRUCTURE.py**
  * Add Structure `INSceneVO`
  * Modify Attributes
    ```
    AssetFilterParam 
        New Attributes:
        ['alias', 'assetName', 'fetchData']

    INQGetPrjBusinessFilter 
        New Attributes:
        ['fetchData', 'projectIds', 'projectName']

    INQProjectVO 
        New Attributes:
        ['type']

    INTaskBaseObj 
        New Attributes:
        ['privilege_end_time', 'privilege_start_time']

    ShotFilterParam 
        New Attributes:
        ['fetchData', 'shotName']

    TaskFilterParam 
        New Attributes:
        ['fetchData']
    ```

### removed

* **IN_COMMON config.json** [`set_in_common_variables`]
  * removed maya IN information

## [1.0.15.2] - 2020-11-6

### Updated

* **IN_PYTHON_API** [`set_in_common_variables`]
  * When trying to modify the WS_IN_MAPPING_DIRECTORY variable, update API_CLIENT synchronously

## [1.0.15.1] - 2020-11-6

### Updated

* **example** [`DCCs`]
  * demonstrate how to modify the IN mapping path by adding a simple line of code

## [1.0.15] - 2020-11-6

### Added

* **IN_COMMON** [`set_in_common_variables`, `get_in_common_variables`]
  * the prototype of method `def set_in_common_variables(variable_name, variable_value, *args, **kwargs):`

## [1.0.14] - 2020-11-6

### Fixed

* **IN_COMMON** [`get_map_path`, `check_config`]
  * Cancel the exception thrown when the mapped path does not exist

## [1.0.13.1] - 2020-11-5

### Added

* **CHANGELOG.md**
  * Flip the update history display

## [1.0.13] - 2020-11-5

### Added

* **IN_COMMON, config.json**
  * add maya variable for IN info

## [1.0.12.4] - 2020-11-5

### Updated

* **IN_API_CONFIG**
  * modify CRLF 2 LF

## [1.0.12.3] - 2020-11-5

### Updated

* update `src/setup/setup_release.bat`
  * Suspend deployment to internal

## [1.0.12.2] - 2020-11-5

### Updated

* update `src/setup/setup_release.bat`
  * deploy to internal use service

## [1.0.12.1] - 2020-11-5

### Added

* added `src/setup/setup_release.bat`

## [1.0.12] - 2020-11-4

### Updated

* **IN_API_SERVER_MANAGER** **IN_PYTHON_API**
  * using `print("%s" % (msg))` instead of `print("{}".format(msg))`

## [1.0.11] - 2020-11-4

### Updated

* **IN_PYTHON_API** [`data_flow_get_task_files_record`]
  * The assembly output file is in the same format as the intermediate file, if the output file is a project file

## [1.0.10] - 2020-11-3

### Added

* **IN_API_SERVER_MANAGER**
  * Chinese Supported

### Updated

* **IN_COMMON** [`get_map_path`]
  * raise `RuntimeError` if the map-path doesn't exists

## [1.0.9] - 2020-11-3

### Updated

* **IN_PYTHON_API_FUNC**

## [1.0.8] - 2020-11-3

### Updated

* **IN_PYTHON_API** [`data_flow_get_task_list`]

  * remove relative path from returned data
* **IN_PYTHON_API** [`data_flow_update_all_task_files`]

  * using new path `<IN_MAP_PATH + config + file_dont_update.json>`

## [1.0.7] - 2020-11-3

### Fixed

* **IN_COMMON** [`Decorator - exception_capture`]
  * return `seg_return` format

## [1.0.6] - 2020-11-3

### Fixed

* **IN_COMMON** [`logger`]
  * Fixed unnormaly cases when using customize logger, you can using logging and costomize-logger bothly

### Added

* **IN_API_CLIENT** [`api_call`]
  * added and set up the `customize_timeout` default is True for supported customize overtime handling

## [1.0.5] - 2020-11-3

### Rollback

* **IN_API_SERVER_MANAGER**

  * Rollback to beta1.0.3
* **config.json** [`CLIENT_API_CALL_OVERTIME`]

  * Extend to 15 Sec.

## [1.0.4] - 2020-11-2

### Fixed

* **IN_API_CLIENT** [`uploadOutputFile`]
  * fix in_map_dir

## [1.0.3] - 2020-11-2

### Added

* **IN_COMMON** [`get_map_path`]
  * try to get the map_path from `%home%/.intelligentNodes/usersetting.ini`(windows) `$home./intelligentNodes/usersetting.ini`(linux) at first

### Added

* **IN_SERVER** [`run_server`]
  * add IN_COMMON.check_config() for ensure that the configuration is correct before starting the service

## [1.0.2] - 2020-11-2

### Fixed

* **IN_PYTHON_API** [`Decorator - check_connected`]
  * fixed return

## [1.0.1] - 2020-10-30

### Fixed

* **IN_PYTHON_API** [`data_flow_change_task_status`]
  * add Raise Attribute error when update task status with Paused(8)

### Added

* **CHNAGELOG.md** file

### Changed

* **CHNAGELOG.md**
  * rename Changelog to CHNAGELOG.md

## [1.0.0] - 2020-10-30

* Release
