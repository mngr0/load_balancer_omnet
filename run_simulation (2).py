#!/usr/bin/env python

import os
import re
import subprocess
import sys
from argparse import ArgumentParser
from pathlib import Path

QUEUEING_PATH = "/opt/omnetpp/samples/queueinglib"
OMNET_WORKSPACE = Path("/home/orang3/omnet/samples/")
OUT_PATH = Path("/home/orang3/Uni/Magistrale/Simulazione di Sistemi/workspace/")
SCAVETOOL_OUT = "scavetool.csv"
EXPORT = "export/"


def get_args():
    parser = ArgumentParser(
        description=f"Utility to run OMNET++ simulation and export CSV from .vec files"
    )
    parser.add_argument("project", nargs="?", help="The OMNET++ Project name")
    parser.add_argument(
        "-c", "--config",
        default="General",
        help="OMNET++'s configuration name. Defaults to 'General'")
    return parser.parse_args()


def config_exists(sim_name, config, cwd):
    stdout = subprocess.run(
        f"./{sim_name} -a -s",
        cwd=cwd,
        shell=True,
        capture_output=True
    ).stdout.decode("utf-8")

    pattern = re.compile(r"Config {}: \d+".format(config))
    return len(pattern.findall(stdout)) > 0


def build_simulation(cwd):
    subprocess.run(
        f"opp_makemake -f --deep -O out -I. -I{QUEUEING_PATH} -L{QUEUEING_PATH} -lqueueinglib -u Cmdenv --mode release",
        shell=True, cwd=cwd)
    subprocess.run("make all", shell=True, cwd=cwd)


def run_simulation(sim_name, config, cwd, verbose=False):
    command = f"opp_runall -j8 -b4 ./{sim_name} -u Cmdenv -c {config}"
    if not verbose:
        command += " > /dev/null"
    subprocess.run(
        command,
        shell=True,
        cwd=cwd
    )


def export_vecs(out_file, cwd):
    subprocess.run(
        f"scavetool x *.vec -F CSV-R -o '{out_file}' && echo {out_file}",
        shell=True,
        cwd=cwd
    )


def remove_old_results(scavetool_csv, export_d, results_d):
    # scavetool output
    if scavetool_csv.is_file():
        os.remove(scavetool_csv)
    # old omnet results
    os.system(
        f"rm -rf '{results_d}'",
    )
    # create temporary export dir if necessary and remove its eventual contents
    os.system(
        f"rm -rf '{export_d}'",
    )
    os.makedirs(export_d)


if __name__ == "__main__":

    ARGS = get_args()

    project_name = ARGS.project
    project_root = Path(OMNET_WORKSPACE, project_name)
    config_name = ARGS.config

    if not project_root.is_dir():
        raise ValueError(f"Error: no project called {project_name} found in {OMNET_WORKSPACE}")
    elif not config_exists(project_name, config_name, project_root):
        raise ValueError(f"Error: {config_name} is not a configuration of {project_name}")
    else:

        stool_csv = Path(OUT_PATH, project_name, SCAVETOOL_OUT)
        export_dir = Path(OUT_PATH, project_name, EXPORT)
        omnet_results_dir = Path(project_root, "results/")

        build_simulation(project_root)

        remove_old_results(stool_csv, export_dir, omnet_results_dir)

        run_simulation(project_name, config_name, project_root, True)

        print("Exporting vec")

        export_vecs(stool_csv, omnet_results_dir)

        sys.exit(0)
