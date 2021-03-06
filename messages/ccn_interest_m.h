//
// Generated file, do not edit! Created by opp_msgc 4.2 from messages/ccn_interest.msg.
//

#ifndef _CCN_INTEREST_M_H_
#define _CCN_INTEREST_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>messages/ccn_interest.msg</tt> by opp_msgc.
 * <pre>
 * message ccn_interest{
 * 	@customize(true);
 * 	unsigned long chunk;
 * 	double hops = 0;
 * 	bool closest=false;
 * 	abstract int path[];
 * 	unsigned long repository;
 * }
 * </pre>
 *
 * ccn_interest_Base is only useful if it gets subclassed, and ccn_interest is derived from it.
 * The minimum code to be written for ccn_interest is the following:
 *
 * <pre>
 * class ccn_interest : public ccn_interest_Base
 * {
 *   private:
 *     void copy(const ccn_interest& other) { ... }

 *   public:
 *     ccn_interest(const char *name=NULL, int kind=0) : ccn_interest_Base(name,kind) {}
 *     ccn_interest(const ccn_interest& other) : ccn_interest_Base(other) {copy(other);}
 *     ccn_interest& operator=(const ccn_interest& other) {if (this==&other) return *this; ccn_interest_Base::operator=(other); copy(other); return *this;}
 *     virtual ccn_interest *dup() const {return new ccn_interest(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from ccn_interest_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(ccn_interest);
 * </pre>
 */
class ccn_interest_Base : public ::cMessage
{
  protected:
    unsigned long chunk_var;
    double hops_var;
    bool closest_var;
    unsigned long repository_var;

  private:
    void copy(const ccn_interest_Base& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ccn_interest_Base&);
    // make constructors protected to avoid instantiation
    ccn_interest_Base(const char *name=NULL, int kind=0);
    ccn_interest_Base(const ccn_interest_Base& other);
    // make assignment operator protected to force the user override it
    ccn_interest_Base& operator=(const ccn_interest_Base& other);

  public:
    virtual ~ccn_interest_Base();
    virtual ccn_interest_Base *dup() const {throw cRuntimeError("You forgot to manually add a dup() function to class ccn_interest");}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned long getChunk() const;
    virtual void setChunk(unsigned long chunk);
    virtual double getHops() const;
    virtual void setHops(double hops);
    virtual bool getClosest() const;
    virtual void setClosest(bool closest);
    virtual void setPathArraySize(unsigned int size) = 0;
    virtual unsigned int getPathArraySize() const = 0;
    virtual int getPath(unsigned int k) const = 0;
    virtual void setPath(unsigned int k, int path) = 0;
    virtual unsigned long getRepository() const;
    virtual void setRepository(unsigned long repository);
};


#endif // _CCN_INTEREST_M_H_
