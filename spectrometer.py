from module_with_functions import *

def spectrometer_reading():

   arduinoData = ser.readlines()

   N = str(arduinoData).split('\r\n')

   F=['']

   for i in range(len(N[0])):
        if N[0][i].isdigit():
            F[0]=F[0]+(N[0][i])
        elif (N[0][i]==',' and N[0][i-1].isdigit()):
            F[0]=F[0]+','
        elif (N[0][i]=='.' and N[0][i-1].isdigit()):
            F[0]=F[0]+'.'


   F=F[0].split(',')

   F.pop()
   for i in range(len(F)):
       F[i]=float(F[i])

   def Corr(a,b):
       average_a=0
       average_b=0
       Cov_ab=0
       Stdv_a=0
       Stdv_b=0
       Correlation=0

       for i in range(len(a)):
           average_a=average_a+a[i]
           average_b=average_b+b[i]
           average_a=average_a/(len(a))
           average_b=average_b/(len(b))

       for i in range(len(a)):
           Cov_ab=(a[i]-average_a)*(b[i]-average_b)+Cov_ab
           Cov_ab=Cov_ab/(len(a)-1)

       for i in range(len(a)):
           Stdv_a=Stdv_a+(a[i]-average_a)**2
           Stdv_b=Stdv_b+(b[i]-average_b)**2
           Stdv_a=(Stdv_a/(len(a)-1))**0.5
           Stdv_b=(Stdv_b/(len(b)-1))**0.5

       Correlation=round(Cov_ab/(Stdv_a*Stdv_b),2)

       return(Correlation)
      
   def slope(a,b):
       Sumproduct=0
       Sumsqr=0
       slopevalue=0
       for i in range(len(b)):
           Sumproduct=b[i]*a[i]+Sumproduct
           Sumsqr=b[i]**2+Sumsqr

       slopevalue=Sumproduct/Sumsqr
       if slopevalue<1:
           return(slopevalue)
       else:
           slopevalue=1/slopevalue
           return(slopevalue)

   Data_Spectrometer = [['can (decentralised)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.51, 3.24, 3.56, 4.35, 3.11, 5.85, 3.95, 10.86], 'Aluminium', 0.39, 0.44, 0.48, 0.53, 'Bin 3'],
                 ['can (central)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.51, 3.24, 3.56, 4.35, 3.11, 5.85, 3.95, 10.86], 'Aluminium', 0.39, 0.44, 0.48, 0.53, 'Bin 3'],
                 # ['can (central)', [81.06, 31.15, 23.74, 18.54, 26.8, 18.79, 30.33, 30.83, 44.96, 18.01, 13.29, 5.09, 6.23, 5.22, 8.23, 11.71, 6.59, 12.83], 'Aluminium', 0.03, 0.05, 0.12, 0.12, 'Bin 3'],
                 ['can (random)', [20.51, 9.44, 12.88, 3.53, 5.36, 4.87, 7.86, 9.04, 9.57, 8.06, 10.22, 3.29, 4.45, 4.35, 3.66, 7.03, 3.95, 11.85], 'Aluminium', 0.02, 0.05, 0.39, 0.45, 'Bin 3'],
                 # ['can (standing central)', [91.81, 223.71, 368.9, 37.07, 179.77, 246.33, 31.45, 39.87, 83.81, 18.01, 40.89, 12.49, 21.35, 16.53, 11.89, 12.88, 21.08, 20.73], 'Aluminium', 0.0, 0.0, 0.02, 0.03, 'Bin 3'],
                 # ['can (central)', [136.63, 58.52, 48.76, 39.72, 53.59, 57.07, 54.48, 59.54, 84.16, 28.44, 27.6, 8.33, 8.0, 6.96, 12.8, 21.08, 9.88, 14.61], 'Aluminium', 0.0, 0.06, 0.11, 0.12, 'Bin 3'],
                 ['can (decentralised)', [13.18, 5.66, 6.44, 3.53, 5.36, 4.87, 7.47, 8.51, 9.22, 7.58, 9.3, 3.24, 3.56, 4.35, 2.83, 5.85, 3.95, 10.86], 'Aluminium', 0.39, 0.44, 0.48, 0.53, 'Bin 3'],
                 ['can (decentralised)', [12.7, 5.66, 6.35, 3.53, 5.36, 4.87, 7.52, 8.51, 9.22, 7.58, 9.2, 3.24, 3.56, 4.35, 2.92, 5.85, 3.95, 10.86], 'Aluminium', 0.39, 0.44, 0.48, 0.53, 'Bin 3'],
                 ['can (random)', [15.63, 7.55, 10.12, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.91, 3.24, 3.56, 4.35, 3.29, 5.85, 3.95, 11.85], 'Aluminium', 0.15, 0.41, 0.42, 0.48, 'Bin 3'],
                 ['can (standing random)', [13.67, 6.61, 7.36, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 10.22, 3.24, 3.56, 4.35, 3.29, 5.97, 3.95, 11.45], 'Aluminium', 0.39, 0.41, 0.48, 0.52, 'Bin 3'],
                 ['can (central inclined)', [112.32, 25.49, 18.4, 22.07, 18.37, 11.83, 14.04, 26.05, 41.51, 25.12, 11.24, 4.16, 5.34, 4.52, 4.57, 7.03, 5.27, 12.83], 'Aluminium', 0.0, 0.06, 0.06, 0.06, 'Bin 3'],
                 ['can (decentralised inclined)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.4, 3.24, 3.56, 4.35, 3.38, 5.97, 3.95, 10.86], 'Aluminium', 0.39, 0.44, 0.48, 0.53, 'Bin 3'],
                 ['can (corner inclined)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.61, 3.24, 3.56, 4.35, 3.02, 5.85, 3.95, 10.86], 'Aluminium', 0.39, 0.44, 0.48, 0.53, 'Bin 3'],
                 ['bottle (central)', [11.72, 5.66, 7.36, 6.18, 10.72, 11.14, 12.92, 11.21, 15.45, 7.58, 12.27, 4.16, 3.56, 4.35, 5.58, 12.88, 5.27, 10.86], 'PET', 0.0, 0.0, 0.02, 0.06, 'Bin 2'],
                 ['bottle (decentralised)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.3, 3.24, 3.56, 4.35, 2.92, 5.85, 3.95, 10.86], 'PET', 0.44, 0.47, 0.52, 0.55, 'Bin 2'],
                 ['bottle (random)', [13.67, 5.66, 6.44, 3.53, 6.81, 6.82, 14.43, 9.57, 10.38, 7.58, 10.22, 3.98, 3.56, 4.35, 3.66, 8.67, 3.95, 10.86], 'PET', 0.0, 0.0, 0.45, 0.5, 'Bin 2'],
                 # ['bottle (central)', [56.75, 19.26, 14.72, 14.12, 17.76, 10.44, 20.22, 24.45, 39.2, 14.69, 11.24, 4.16, 5.34, 5.22, 7.31, 8.2, 6.52, 12.24], 'PET', 0.03, 0.08, 0.11, 0.14, 'Bin 2'],
                 ['bottle (decentralised)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.3, 3.24, 3.56, 4.35, 2.92, 5.85, 3.95, 10.86], 'PET', 0.44, 0.47, 0.52, 0.55, 'Bin 2'],
                 ['bottle (random)', [12.7, 5.66, 5.7, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.2, 3.24, 3.56, 4.35, 2.74, 5.85, 3.95, 10.86], 'PET', 0.42, 0.48, 0.53, 0.55, 'Bin 2'],
                 ['contaminated bottle (decentralised)', [13.68, 6.13, 6.16, 4.06, 6.35, 5.91, 8.59, 9.41, 10.83, 7.91, 9.71, 3.38, 3.65, 4.35, 3.2, 6.2, 4.02, 10.96], 'PET contaminated', 0.48, 0.53, 0.58, 0.65, 'Bin 1'],
                 ['contaminated bottle (central)', [10.74, 4.72, 3.68, 3.53, 6.12, 6.96, 10.67, 11.16, 14.99, 8.53, 11.24, 3.7, 4.27, 4.35, 4.57, 8.2, 3.95, 11.45], 'PET contaminated', 0.02, 0.05, 0.21, 0.56, 'Bin 1'],
                 ['contaminated bottle (random)', [12.7, 5.66, 5.61, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.2, 3.24, 3.56, 4.35, 3.29, 5.85, 3.95, 10.86], 'PET contaminated', 0.47, 0.55, 0.59, 0.62, 'Bin 1'],
                 # ['bottle (central)', [16.6, 5.66, 5.52, 7.06, 8.42, 6.26, 11.23, 13.29, 34.59, 12.32, 10.73, 4.16, 4.45, 4.35, 6.4, 9.37, 4.61, 11.65], 'PET', 0.0, 0.03, 0.03, 0.14, 'Bin 2'],
                 ['bottle (decentralised)', [13.67, 5.66, 6.35, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.2, 3.24, 3.56, 4.35, 3.11, 5.85, 3.95, 10.86], 'PET', 0.44, 0.47, 0.52, 0.55, 'Bin 2'],
                 ['bottle (random)', [16.6, 7.55, 9.48, 1.77, 3.83, 3.48, 5.68, 6.91, 6.92, 7.58, 9.2, 3.24, 3.56, 4.35, 2.74, 5.85, 3.95, 11.85], 'PET', 0.03, 0.2, 0.44, 0.47, 'Bin 2'],
                 ['bottle (central)', [27.54, 12.55, 6.9, 10.15, 12.02, 4.94, 10.05, 12.34, 16.71, 9.24, 9.2, 3.24, 4.45, 4.35, 4.57, 6.91, 4.61, 11.85], 'PET', 0.0, 0.05, 0.09, 0.36, 'Bin 2'],
                 ['bottle (decentralised)', [13.48, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.2, 3.24, 3.56, 4.35, 3.02, 5.85, 3.95, 10.86], 'PET', 0.44, 0.47, 0.52, 0.55, 'Bin 2'],
                 ['bottle (random)', [28.32, 9.35, 6.44, 18.54, 29.09, 10.44, 25.84, 28.17, 43.12, 15.17, 9.4, 4.16, 5.34, 4.35, 7.31, 9.37, 6.59, 11.85], 'PET', 0.02, 0.03, 0.05, 0.09, 'Bin 2'],
                 # ['plastic lid', [29.3, 11.33, 8.28, 12.36, 15.31, 9.74, 21.34, 22.33, 31.13, 11.37, 11.24, 4.16, 4.45, 4.35, 6.4, 8.2, 4.61, 11.85], 'Polystyrene', 0.0, 0.08, 0.18, 0.23, 'Bin 1'],
                 ['plastic lid (decentralised)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.2, 3.24, 3.56, 4.35, 3.29, 5.85, 3.95, 10.86], 'Polystyrene', 0.48, 0.53, 0.58, 0.62, 'Bin 1'],
                 ['plastic lid (central)', [17.29, 13.21, 27.6, 3.53, 11.48, 17.33, 10.67, 11.7, 10.38, 8.06, 14.21, 4.63, 4.45, 4.79, 3.66, 8.2, 5.27, 11.85], 'Polystyrene', 0.0, 0.0, 0.03, 0.06, 'Bin 1'],
                 ['black plastic lid (central)', [8.79, 3.78, 3.68, 1.77, 3.29, 2.78, 5.62, 6.38, 6.92, 6.63, 9.2, 3.24, 3.56, 4.35, 2.74, 5.85, 3.29, 10.86], 'Polystyrene', 0.0, 0.2, 0.47, 0.55, 'Bin 1'],
                 ['black plastic lid (decentralised)', [12.7, 5.66, 6.35, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.3, 3.24, 3.56, 4.35, 3.2, 5.85, 3.95, 10.86], 'Polystyrene', 0.47, 0.52, 0.58, 0.62, 'Bin 1'],
                 ['paper cup', [17.58, 11.33, 17.48, 5.3, 11.48, 14.62, 13.48, 13.29, 16.14, 8.77, 12.27, 4.16, 4.45, 4.96, 4.57, 8.2, 5.27, 11.85], 'Paper', 0.0, 0.0, 0.02, 0.03, 'Bin 1'],
                 # ['paper cup (standing central)', [211.93, 92.5, 132.47, 71.5, 107.57, 116.24, 131.48, 136.62, 217.91, 72.04, 53.98, 18.04, 15.12, 12.35, 34.75, 58.54, 25.03, 20.73], 'Paper', 0.0, 0.02, 0.06, 0.09, 'Bin 1'],
                 ['paper cup (decentralised)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 9.04, 10.38, 7.58, 10.12, 3.24, 3.56, 4.35, 3.66, 6.32, 3.95, 10.96], 'Paper', 0.38, 0.44, 0.53, 0.56, 'Bin 1'],
                 ['paper cup (central)', [22.46, 7.55, 7.36, 16.77, 18.37, 13.22, 41.56, 30.83, 47.27, 12.8, 13.29, 5.55, 4.45, 4.79, 9.32, 16.39, 4.61, 11.85], 'Paper', 0.0, 0.0, 0.03, 0.05, 'Bin 1'],
                 ['paper cup (decentralised)', [13.67, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 9.04, 9.22, 7.58, 10.22, 3.24, 3.56, 4.35, 3.66, 7.03, 3.95, 11.06], 'Paper', 0.38, 0.42, 0.5, 0.55, 'Bin 1'],
                 # ['paper cup (random)', [99.62, 38.7, 40.48, 9.71, 16.08, 14.27, 9.55, 14.72, 20.75, 17.06, 12.27, 4.16, 7.12, 6.0, 4.57, 7.15, 6.59, 13.82], 'Paper', 0.0, 0.02, 0.06, 0.12, 'Bin 1'],
                 ['cardboard sleeve', [10.74, 5.66, 8.28, 2.65, 6.12, 10.44, 8.42, 9.04, 9.22, 7.58, 14.31, 4.16, 4.45, 5.22, 3.84, 9.37, 5.27, 11.85], 'Cardboard', 0.0, 0.0, 0.0, 0.14, 'Bin 1'],
                 ['cardboard (decentralised)', [12.7, 5.66, 5.52, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.51, 3.24, 3.56, 4.35, 3.66, 5.85, 3.95, 10.86], 'Cardboard', 0.42, 0.48, 0.55, 0.56, 'Bin 1'],
                 ['cardboard sleeve (central)', [12.7, 5.66, 6.44, 3.53, 5.36, 4.87, 7.3, 8.51, 9.22, 7.58, 10.22, 3.24, 3.56, 4.35, 3.57, 5.97, 3.95, 11.85], 'Cardboard', 0.42, 0.47, 0.53, 0.55, 'Bin 1'],
                 ['box (central)', [11.72, 5.66, 6.62, 3.53, 6.5, 5.57, 9.72, 11.7, 14.99, 9.0, 10.22, 3.7, 4.45, 4.35, 4.57, 8.2, 5.27, 11.85], 'Cardboard', 0.05, 0.15, 0.47, 0.56, 'Bin 1'],
                 ['box (decentralised)', [13.67, 5.66, 6.35, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.3, 3.24, 3.56, 4.35, 3.66, 6.32, 3.95, 10.86], 'Cardboard', 0.44, 0.48, 0.53, 0.58, 'Bin 1'],
                 ['box (random)', [12.7, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.4, 3.24, 3.56, 4.35, 3.66, 6.09, 3.95, 10.86], 'Cardboard', 0.42, 0.48, 0.53, 0.56, 'Bin 1'],
                 # ['squashed paper (central)', [26.37, 16.05, 10.12, 21.18, 21.44, 11.83, 30.33, 27.11, 41.51, 13.27, 11.55, 4.63, 5.34, 5.22, 8.23, 11.71, 5.27, 11.85], 'Paper', 0.02, 0.03, 0.03, 0.06, 'Bin 1'],
                 ['squashed paper (decentralised)', [13.48, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.4, 3.24, 3.56, 4.35, 3.57, 5.97, 3.95, 10.86], 'Paper', 0.39, 0.44, 0.5, 0.55, 'Bin 1'],
                 ['squashed paper (random)', [16.6, 7.55, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 8.06, 10.02, 3.24, 3.65, 4.35, 3.66, 5.85, 3.95, 11.85], 'Paper', 0.39, 0.42, 0.48, 0.52, 'Bin 1'],
                 ['sheet of paper', [59.68, 43.61, 44.8, 26.48, 31.39, 32.02, 33.14, 33.49, 50.73, 20.85, 19.42, 6.48, 6.23, 6.09, 9.14, 15.22, 7.25, 12.83], 'Paper', 0.0, 0.02, 0.05, 0.08, 'Bin 1'],
                 # ['sheet of paper (inclined)', [13.67, 6.52, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.51, 3.24, 3.56, 4.35, 3.2, 5.85, 3.95, 10.86], 'Paper', 0.39, 0.45, 0.5, 0.55, 'Bin 1'],
                 ['small paper', [12.8, 5.66, 5.52, 6.18, 14.55, 11.83, 16.85, 34.55, 54.19, 19.76, 16.36, 5.55, 6.23, 6.09, 8.59, 11.59, 6.59, 12.05], 'Paper', 0.0, 0.02, 0.02, 0.05, 'Bin 1'],
                 ['small paper (decentralised)', [12.7, 5.66, 5.52, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.4, 3.24, 3.56, 4.35, 3.29, 5.85, 3.95, 10.86], 'Paper', 0.38, 0.44, 0.52, 0.53, 'Bin 1'],
                 # ['small paper (random)', [13.67, 5.66, 5.52, 3.53, 5.36, 4.87, 7.86, 8.51, 10.38, 9.0, 9.4, 3.24, 3.56, 4.35, 3.48, 5.85, 3.95, 10.86], 'Paper', 0.38, 0.44, 0.52, 0.55, 'Bin 1'],
                 # ['small post it (central)', [47.86, 20.68, 15.27, 12.36, 16.84, 11.83, 14.66, 24.99, 38.05, 18.96, 12.17, 4.16, 6.23, 5.22, 5.58, 8.2, 5.93, 12.83], 'Paper', 0.03, 0.11, 0.11, 0.14, 'Bin 1'],
                 ['small post it (decentralised)', [12.7, 5.66, 6.26, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.3, 3.24, 3.56, 4.35, 3.11, 5.85, 3.95, 10.86], 'Paper', 0.38, 0.44, 0.5, 0.55, 'Bin 1'],
                 ['crisp packet', [42.97, 19.82, 21.16, 17.65, 23.73, 18.1, 25.27, 14.35, 16.14, 9.48, 12.27, 4.63, 4.45, 5.22, 8.23, 17.56, 6.59, 11.85], 'Non-recyclable', 0.0, 0.0, 0.03, 0.06, 'Bin 1'],
                 # ['crisp packet (decentralised)', [14.65, 5.66, 6.44, 3.53, 5.36, 4.87, 8.42, 9.04, 10.03, 7.58, 9.51, 3.24, 3.56, 4.35, 3.66, 6.79, 3.95, 10.86], 'Non-recyclable', 0.47, 0.5, 0.58, 0.61, 'Bin 1'],
                 ['squashed crisp packet (decentralised)', [36.04, 17.93, 33.12, 4.41, 9.19, 11.14, 8.42, 11.11, 11.53, 9.95, 11.24, 3.7, 4.45, 4.35, 3.66, 7.03, 5.27, 12.83], 'Non-recyclable', 0.0, 0.0, 0.03, 0.09, 'Bin 1'],
                 # ['plastic packaging', [19.53, 8.5, 8.28, 5.3, 9.19, 6.96, 11.23, 14.35, 24.21, 12.32, 10.22, 3.7, 4.45, 4.35, 4.57, 7.03, 4.61, 11.85], 'Non-recyclable', 0.0, 0.08, 0.15, 0.62, 'Bin 1'],
                 # ['plastic packaging', [12.7, 5.66, 5.52, 4.41, 6.12, 4.87, 9.55, 10.1, 13.84, 7.58, 9.2, 3.24, 3.56, 4.35, 3.66, 7.03, 3.95, 10.86], 'Non-recyclable', 0.05, 0.48, 0.55, 0.61, 'Bin 1'],
                 # ['plastic packaging', [13.67, 5.66, 6.44, 2.65, 5.36, 4.87, 7.86, 9.04, 10.38, 8.06, 10.22, 3.24, 3.74, 4.35, 3.66, 5.85, 3.95, 11.75], 'Non-recyclable', 0.47, 0.53, 0.59, 0.61, 'Bin 1'],
                 # ['wooden fork (central)', [14.65, 7.55, 8.92, 5.3, 7.66, 7.66, 10.67, 12.76, 16.14, 9.0, 11.24, 3.7, 4.45, 4.35, 4.57, 7.03, 4.61, 11.85], 'Wood', 0.03, 0.47, 0.58, 0.64, 'Bin 1'],
                 ['wooden fork (decentralised)', [12.7, 5.66, 5.52, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.2, 3.24, 3.56, 4.35, 3.02, 5.85, 3.95, 10.86], 'Wood', 0.47, 0.52, 0.59, 0.62, 'Bin 1'],
                 ['wooden forks ', [12.7, 5.66, 5.52, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.4, 3.24, 3.56, 4.35, 3.38, 7.03, 3.95, 10.86], 'Wood', 0.47, 0.53, 0.58, 0.62, 'Bin 1'],
                 # ['sandwich packet', [50.79, 60.41, 83.72, 22.95, 35.98, 42.46, 23.03, 29.88, 46.12, 18.96, 20.44, 6.48, 7.12, 6.96, 8.23, 12.88, 9.88, 13.82], 'Cardboard', 0.0, 0.0, 0.05, 0.06, 'Bin 1'],
                 ['sandwich packet (decentralised)', [12.7, 5.66, 6.44, 3.53, 5.36, 4.87, 7.86, 8.51, 9.22, 7.58, 9.61, 3.24, 3.56, 4.35, 3.57, 5.97, 3.95, 10.86], 'Cardboard', 0.42, 0.48, 0.53, 0.56, 'Bin 1']]

   Correlation_items_families=[0,0,0,0,0,0]
   Correlation_items=[]
   for i in range(len(Data_Spectrometer)):
       Correlation_items.append(0)
   Slope_items=[]
   for i in range(len(Data_Spectrometer)):
      Slope_items.append(0)

   Count_paper=0
   Count_PET=0
   Count_polystyrene=0
   Count_aluminium=0
   Count_Wood=0
   Count_Non_recyclable=0
   Families=['Paper','PET','Polystyrene','Aluminium', 'Wood', 'Non-recyclable']

   Spectrometersplit = [[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]

   AverageSpectrometer = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
   items_correlation=0

   for i in range(0,18):
       for j in range(0,10):
           Spectrometersplit[j][i]=F[i+j*18]


   for i in range(0,18):
       for j in range(0,10):
           AverageSpectrometer[i]= AverageSpectrometer[i]+Spectrometersplit[j][i]

       AverageSpectrometer[i]=round(AverageSpectrometer[i]/10,2)

   for i in range(len(Data_Spectrometer)):
        Correlation_items[i]=Corr(Data_Spectrometer[i][1],AverageSpectrometer)
         
   for i in range(len(Data_Spectrometer)):
      Slope_items[i]=slope(Data_Spectrometer[i][1],AverageSpectrometer)  

   Baseline_index=0
   if max(Correlation_items)>0.95:
       Baseline_index=3
   if max(Correlation_items)>0.9:
       Baseline_index=4
   if max(Correlation_items)>0.85:
       Baseline_index=5
   if max(Correlation_items)>0.8:
       Baseline_index=6

   Criteria= 0.85
   Percentage=0
   Index=0

   for i in range(len(Correlation_items)):
       if Correlation_items[i]>Criteria:
            if Slope_items[i] > Percentage:
               Percentage= Slope_items[i]
               Index= i
               
   #print(Data_Spectrometer[Index][7],Data_Spectrometer[Index][2],Slope_items[Index],Correlation_items[Index])
   print(Data_Spectrometer[Index][7])
