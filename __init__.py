import os
import sys
tank_dir = os.path.dirname(__file__)
sys.path.append(tank_dir)
sys.path.append(os.path.join(tank_dir, "yaml"))
from python import yaml
from python import sgtk
