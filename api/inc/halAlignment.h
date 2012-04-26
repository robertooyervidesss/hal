/*
 * Copyright (C) 2012 by Glenn Hickey (hickey@soe.ucsc.edu)
 *
 * Released under the MIT license, see LICENSE.txt
 */

#ifndef _HALALIGNMENT_H
#define _HALALIGNMENT_H

#include <string>
#include "halDefs.h"

namespace hal {

/** 
 * Interface for a hierarhcical alignment
 * TODO: revise tree-related stuff (maybe move to genome class)
 * or maybe just embed in the hdf5 hierarchy...
 */
class Alignment
{
public:

   /** Create new alignment (overwriting any existing alignments)
    * @param alignmentPath location on disk */
   virtual void createNew(const std::string& alignmentPath) = 0;

   /** Open an existing alignment 
    * @param alignmentPath location on disk 
    * @param readOnly access flag */
   virtual void open(const std::string& alignmentPath, 
                     bool readOnly) = 0;

   /** Close the alignment */
   virtual void close() = 0;
   
   /** Add a new genome to the alignment
    * @param name name of new genome in alignment (must be unique)
    * @param parent name of parent genome in tree (must exist)
    * @param branchLength distance between new genome and parent */
   virtual Genome* addLeafGenome(const std::string& name,
                                   const std::string& parentName,
                                   double branchLength) = 0;

   /** Add a new genome as root to the alignment.  The previous root
    * (if exists) will be a child of the new genome
    * @param name name of new genome in alignment (must be unique)
    * @param branchLength distance between new genome and previous root
    * (if exists)*/
   virtual Genome* addRootGenome(const std::string& name,
                                 double branchLength = 0) = 0;

   /** Remove a genome from the alignment 
    * @param path Path of genome to remove */
   virtual void removeGenome(const std::string& name) = 0;

   /** Open an existing genome for reading and updating
    * @param name Name of genome to open */
   virtual const Genome* openGenome(const std::string& name) const = 0;

   /** Open an exsting genome for reading
    * @param name Name of genome to open */
   virtual Genome* openGenome(const std::string& name) = 0;

   /** Get name of root genome (empty string for empty alignment) */
   virtual std::string getRootName() const = 0;

   /** Get name of parent genome in the phylogeny (empty string for root)
    * @param name Name of genome */
   virtual std::string getParentName(const std::string& name) const = 0;

   /** Get the branch length between two genomes in the phylogeny 
    * @param parentName name of parent genome
    * @param childName name of child genome */
   virtual double getBranchLength(const std::string& parentName,
                                  const std::string& childName) const = 0;
   
   /** Get names of child genomes in the phylogeny (empty vector for leaves)
    * @param name Name of genome */
   virtual std::vector<std::string> 
   getChildNames(const std::string& name) const= 0;

   /** Get the names of all leaves below a given genome 
    * @param name Name of genome */
   virtual std::vector<std::string>
   getLeafNamesBelow(const std::string& name) const = 0;

   /** Get the number of genomes (including internal ancestors)
    * in the alignment */
   virtual hal_size_t getNumGenomes() const = 0;

   /** Get Alignment's metadata */
   virtual MetaData* getMetaData() = 0;

   /** Get read-only instance of Alignment's metadata */
   virtual const MetaData* getMetaData() const = 0;

   /** Get a newick-formatted phylogeny to the alignment */
   virtual std::string getNewickTree() const = 0;

protected:
   friend class counted_ptr<Alignment>;
   friend class counted_ptr<const Alignment>;
   /** Destructor */
   virtual ~Alignment() = 0;
};

inline Alignment::~Alignment() {}
}
#endif
