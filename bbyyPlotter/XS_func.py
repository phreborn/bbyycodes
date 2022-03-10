import math

SCALE_GGF = 31.02/31.05

### NLO HEFT XS ###                                                                                     
def xs_ggF_chhh(chhh):

    return (0.01027*chhh**2-0.049295*chhh+0.069618)*1000*SCALE_GGF

def xs_ggF_cgghh(cgghh):

    return (0.392434*cgghh**2-0.093177*cgghh+0.031050)*1000* SCALE_GGF

def xs_ggF_ctthh(ctthh):

    return (0.384676*ctthh**2-0.192232*ctthh+0.031050)*1000*SCALE_GGF

def xs_ggF_ctth(ctth):

    return (0.069618*ctth**4-0.049295*ctth**3+0.010727+ctth**2)*1000*SCALE_GGF

def xs_ggF_cggh(cggh):

    return (0.000446*cggh**3+0.010565*cggh**2-0.018022*cggh+0.030123)*1000*SCALE_GGF

##############                                                                                                                                                                                 
def xs_ggF_kl_kt(kl,kt):
    # Formula from combination slide 7 https://indico.cern.ch/event/982063/contributions/4136966/attachments/2160554/3645303/SignalTemplates.pdf                                              
    xs_ggF_kl_kt = kt**2*((kt**2+kl**2/20-399/380*kl*kt)*xs_ggF(0) +(40/38*kl*kt-2/38*kl**2)*xs_ggF(1) + (kl**2-kl*kt)/380*xs_ggF(20))

    return xs_ggF_kl_kt

#Now using values from LHCWHGHHHXGGBGGGXXX                                                                                                                                                     
#SCALE_GGF = 31.02/31.0358   #correct to xs at mH = 125.09                                                                       
SCALE_VBF = 1.723/(4.581-4.245+1.359)


def xs_ggF(kl):
    #https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHWGHH?redirectedfrom=LHCPhysics.LHCHXSWGHH#Latest_recommendations_for_gluon                                                            
    return (70.3874-50.4111*kl+11.0595*kl**2) * SCALE_GGF #XS in fb                                                                                                                            

def xs_VBF(kl):
    #https://indico.cern.ch/event/995807/contributions/4184798/attachments/2175756/3683303/VBFXSec.pdf                                                                                         
    return (4.581-4.245*kl+1.359*kl**2) * SCALE_VBF

def xs_HH(kl):
    return xs_ggF(kl) + xs_VBF(kl)

def xs_chhh(chhh):

    return xs_ggF_chhh(chhh)+xs_VBF(chhh)

### Theory Bands ###

# When adding 2 independent Gaussians (e.g. ggF and VBF XS) we can simply add their means and add their sigmas in quadrature                                                                   
def sigma_upper_ggF(kl):
    #https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHWGHH?redirectedfrom=LHCPhysics.LHCHXSWGHH#Latest_recommendations_for_gluon                                                            
    #add the std on ggF HH due to qcd scale, PDF, and mtop in quadrature                                                                                                                       
    #return xs_ggF(kl) * math.sqrt((max(72.0744-51.7362*kl+11.3712*kl**2, 70.9286-51.5708*kl+11.4497*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2 + 0.026**2)                             
    return xs_ggF(kl) * math.sqrt((max(76.6075 - 56.4818*kl + 12.635*kl**2, 75.4617 - 56.3164*kl + 12.7135*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2)

def sigma_upper_VBF(kl):
    #from klambda = 1                                                                                                                                                                          
    return xs_VBF(kl) * math.sqrt(0.0003**2 + 0.021**2)

def sigma_upper_HH(kl):
    sigma_upper = math.sqrt(sigma_upper_ggF(kl)**2 + sigma_upper_VBF(kl)**2)
    return sigma_upper

def xs_upper_HH(kl):
    return xs_HH(kl) + sigma_upper_HH(kl)

def xs_upper_ggF_HH(kl):
    return xs_ggF(kl) + sigma_upper_ggF(kl)

def sigma_lower_ggF(kl):
    #https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHWGHH?redirectedfrom=LHCPhysics.LHCHXSWGHH#Latest_recommendations_for_gluon                                                            
    #add the std on ggF HH due to qcd scale, PDF, and mtop in quadrature                                                                                                                       
    #return xs_ggF(kl) * math.sqrt((min(66.0621-46.7458*kl+10.1673*kl**2, 66.7581-47.721*kl+10.4535*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2 + 0.026**2)                              
    return xs_ggF(kl) * math.sqrt((min(57.6809 - 42.9905*kl + 9.58474*kl**2, 58.3769 - 43.9657*kl + 9.87094*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2)

def sigma_lower_VBF(kl):
    return xs_VBF(kl) * math.sqrt(0.0004**2 + 0.021**2)


def sigma_lower_HH(kl):
    
    sigma_lower = math.sqrt(sigma_lower_ggF(kl)**2 + sigma_lower_VBF(kl)**2)

    return sigma_lower

def xs_lower_HH(kl):

    xs_lower = xs_HH(kl) - sigma_lower_HH(kl)

    return xs_lower

def xs_lower_ggF_HH(kl):

    xs_lower =  xs_ggF(kl) - sigma_lower_ggF(kl)

    return  xs_lower


dic = {
    "klambda_ggF": {"XS" : xs_ggF, "SM" : 1, "lower" : xs_lower_ggF_HH, "upper" : xs_upper_ggF_HH, "label" : "$\kappa_\lambda $", "edges": [-10,10], "y-range" :  [10, 100000]},
    "klambda_ggF+VBF" : {"XS" : xs_HH, "SM" : 1, "lower" : xs_lower_HH, "upper" : xs_upper_HH, "label" : "$\kappa_\lambda $", "edges": [-10,10], "y-range" :  [10, 100000]},
    "chhh_ggF+VBF" : {"XS" : xs_chhh, "SM" : 1, "label" : "$c_{hhh}$", "edges": [-10,10], "y-range" :  [10, 100000]},
    "chhh" : {"XS" : xs_ggF_chhh, "SM" : 1, "label" : "$c_{hhh}$", "edges": [-10,10], "y-range" :  [5, 100000]},
    "cgghh" : {"XS" : xs_ggF_cgghh, "SM" : 0, "label" : "$c_{gghh}$", "edges": [-1.5,1.5], "y-range" :  [5, 50000]},
    "ctthh" : {"XS" : xs_ggF_ctthh, "SM" : 0, "label" : "$c_{tthh}$", "edges": [-2.0,2.0], "y-range" :  [5, 50000]},
    "ctth" : {"XS" : xs_ggF_ctth, "SM" : 1, "label" : "$c_{tth}$", "edges": [-10,10], "y-range" :  [10, 100000]},
    "cggh" : {"XS" : xs_ggF_cggh, "SM" : 0, "label" : "$c_{ggh}$", "edges": [-10,10], "y-range" :  [10, 100000]}
}


