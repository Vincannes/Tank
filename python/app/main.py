import os.path
import sys
import json
import yaml
from pprint import pprint
import tank


CONFIG_PATH = "D:\\Desk\\python\\Tank\\config\\template.yml"


def read_templates():
    templates = {}
    with open(CONFIG_PATH, "r") as config:
        templates = yaml.safe_load(config)

    return templates


dictionary = read_templates()
print(dictionary)
json_object = json.dumps(dictionary, indent=0)
# pprint(read_templates())


# créer un objet tank
myTank = tank.Tank()

# appel d'une méthode pour faire avancer le tank
myTank.moveForward()