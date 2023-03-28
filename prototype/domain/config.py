import yaml


def read_templates():
    templates = {}
    with open(r"D:\Desk\python\Tank\config\template.yml", "r") as config:
        templates = yaml.safe_load(config)

    return templates
