import json
import ROOT
import os

from rootpy.io import root_open
from rootpy.plotting import Hist, Hist2D, Hist3D
from rootpy.plotting import set_style
from rootpy.tree import Tree, TreeChain

import argparse

parser = argparse.ArgumentParser(description='Author: O. Rifki')
parser.add_argument('files', type=str, nargs='+', metavar='<file.root>', help='ROOT files containing the jigsaw information. Histograms will be drawn and saved in the file.')
parser.add_argument('--config', required=True, type=str, dest='config', metavar='<file.json>', help='json file containing configurations for making histograms')
parser.add_argument('--out_tdirectory', required=False, type=str, dest='outdir', metavar='', help='TDirectory to store all generated histograms', default='all')
parser.add_argument('--treename', required=False, type=str, dest='treename', metavar='', help='Tree containing the ntuple information', default='oTree')
parser.add_argument('--eventWeight', required=False, type=str, dest='eventWeightBranch', metavar='', help='Event Weight Branch name', default='weight')
parser.add_argument('--newOutputs', action='store_true', default=False, help='create new output files for histograms')

# parse the arguments, throw errors if missing any
args = parser.parse_args()

config = json.load(file(args.config))

for f in args.files:
  print "opening {0}".format(f)
  if args.newOutputs:
    in_file = root_open(f, "READ")
    out_file = root_open(os.path.join(os.path.dirname(f), "hists_{0:s}".format(os.path.basename(f))), "RECREATE")
    tree = in_file.get(args.treename)
  else:
    out_file = root_open(f, "UPDATE")
    tree = out_file.get(args.treename)
  # create tdirectory and cd into it
  print "\tmaking tdirectory {0}".format(args.outdir)

  # for each thing to draw, we want to apply a selection on them too
  for cut in config['cuts']:
    innerDir = os.path.join(args.outdir, cut['name'])
    try: out_file.rmdir(innerDir)
    except: pass
    try: out_file.rm(innerDir)
    except: pass
    try: out_file.mkdir(innerDir, recurse=True)
    except: pass
    try: out_file.cd(innerDir)
    except: pass
    # get list of things to draw
    for toDraw in config['draw']:
      histName = toDraw['name']
      histDimension = len(toDraw['draw'].split(':'))
      if "nbins" in toDraw:
        print "\tmaking {4}D histogram {0}\n\t{1} bins from {2} to {3}".format(toDraw['name'], toDraw['nbins'], toDraw['min'], toDraw['max'], histDimension)
        if histDimension == 1:
          h = Hist(toDraw['nbins'], toDraw['min'], toDraw['max'], name=histName)
        elif histDimension == 2:
          h = Hist2D(toDraw['nbins'][0], toDraw['min'][0], toDraw['max'][0],
                     toDraw['nbins'][1], toDraw['min'][1], toDraw['max'][1], name=histName)
        elif histDimension == 3:
          h = Hist2D(toDraw['nbins'][0], toDraw['min'][0], toDraw['max'][0],
                     toDraw['nbins'][1], toDraw['min'][1], toDraw['max'][1],
                     toDraw['nbins'][2], toDraw['min'][2], toDraw['max'][2], name=histName)
        else:
          raise ValueError('I dunno how to handle {0}'.format(toDraw))
      elif "edges" in toDraw:
        print "\tmaking {1}D histogram with bin edges: {0}".format(toDraw['edges'], histDimension)
        if histDimension == 1:
          h = Hist(toDraw['edges'], name=histName)
        elif histDimension == 2:
          h = Hist2D(toDraw['edges'][0], toDraw['edges'][1], name=histName)
        elif histDimension == 3:
          h = Hist2D(toDraw['edges'][0], toDraw['edges'][1], toDraw['edges'][2], name=histName)
        else:
          raise ValueError('I dunno how to handle {0}'.format(toDraw))
      else:
        print "ERROR: problem configuring the binning of the histograms..."
        exit()
      # things look ok, so we draw to the histogram
      print "\t\tdrawing {0}\n\t\twith cut ({1})*({2})".format(toDraw['draw'], args.eventWeightBranch, cut['name'])
      tree.Draw(toDraw['draw'], '({0:s})*({1:s})'.format(args.eventWeightBranch, cut['cut']), hist=h)
      samename=h.GetName()
      hnew=h.merge_bins([(-2, -1)]) # merge upper overflow bin
      hnew.SetName(samename)
      # write to file
      print "\t\twriting to file"
      hnew.write()
  out_file.close()
