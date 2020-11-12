# Change Log
All notable changes to this project will be documented in this file.

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