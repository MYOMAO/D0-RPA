#file path will be:
#outLFNDirBase/inputDataset/requestName/time_tag/...
from CRABClient.UserUtilities import config
config = config()
config.General.transferOutputs = True
config.General.requestName = 'Dfinder84'
config.General.workArea = 'crab_projects'
config.JobType.psetName = 'finder_pp_75X_cfg.py'
config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['rssLimit']
config.JobType.pyCfgParams = ['noprint']
config.JobType.outputFiles = ['finder_pp.root']
#config.JobType.process = ['HiForest']
config.Data.inputDataset = '/MinimumBias3/Run2015E-PromptReco-v1/AOD'
config.Data.totalUnits = -1
config.Data.unitsPerJob = 2000
config.Data.inputDBS = 'global'
config.Data.splitting = 'EventAwareLumiBased'
#config.Data.outLFNDirBase = '/store/user/twang/BfinderRun2'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/zshi/test/'
#config.Data.outLFNDirBase = '/afs/lns.mit.edu/user/zzshi/CMSSW_7_5_8_patch3/data/'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/5TeV/Cert_262081-262273_5TeV_PromptReco_Collisions15_25ns_JSON_MuonPhys_v2.txt'
#config.Site.storageSite = 'T2_US_MIT'
config.Site.storageSite = 'T2_CH_CERN'
config.Site.ignoreGlobalBlacklist = True
