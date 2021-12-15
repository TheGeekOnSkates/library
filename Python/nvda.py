import time, ctypes, os, system_info as info

# Load the NVDA client library (assumes the DLL is in the same path as the script)
dll = os.path.join(info.scriptdir(), 'nvdaControllerClient32.dll')
clientLib = ctypes.windll.LoadLibrary(dll)

def is_running():
	"""Tests if NVDA is running"""
	global clientLib
	running = clientLib.nvdaController_testIfRunning()
	return running == 0

def say(text, interrupt = False):
	"""Makes NVDA say a string of text"""
	global clientLib
	if interrupt:
		clientLib.nvdaController_cancelSpeech()
	clientLib.nvdaController_speakText(text)

def stop():
	"""Tells NVDA to stop talking"""
	global clientLib
	clientLib.nvdaController_cancelSpeech()