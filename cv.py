#import cv2
#import numpy as np
#
#img = cv2.imread('E5FLR3.png')
#gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
#edges = cv2.Canny(gray,50,150,apertureSize = 3)
#
#lines = cv2.HoughLines(edges,1,np.pi/180,200)
#for rho,theta in lines[0]:
#    a = np.cos(theta)
#    b = np.sin(theta)
#    x0 = a*rho
#    y0 = b*rho
#    x1 = int(x0 + 1000*(-b))
#    y1 = int(y0 + 1000*(a))
#    x2 = int(x0 - 1000*(-b))
#    y2 = int(y0 - 1000*(a))
#
#    cv2.line(img,(x1,y1),(x2,y2),(0,0,255),2)
#
#cv2.imwrite('houghlines3.jpg',img)
#
#_________________________________________________________________________________
#import cv2
#import numpy as np
#
#img = cv2.imread('E5FLR3.png')
#gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
#edges = cv2.Canny(gray,50,150,apertureSize = 3,  L2gradient= 1 )
#minLineLength = 30
#maxLineGap = 10
#lines = cv2.HoughLinesP(edges,1,np.pi/180,100,minLineLength,maxLineGap)
#corners = cv2.goodFeaturesToTrack(edges, maxCorners = 1000 ,qualityLevel =  0.01, minDistance = 0.1)
#for x1,y1,x2,y2 in lines[0]:
#    cv2.line(img,(x1,y1),(x2,y2),(0,255,0),2)
#    
#for x1,y1 in corners[0]:
#    print x1
##    cv2.circle(img,(x1,y1),1, (0,255,0),2)
#
#dst = cv2.cornerHarris(edges,2,3,0.04)
##print corners
#dst = cv2.dilate(dst,None)
#
#img[dst>0.01*dst.max()]=[0,0,255]
#
#cv2.imwrite('canny.jpg',edges)
#cv2.imwrite('houghlines5.jpg',img)



#_________________________________________________________________________________
#import numpy as np
#import cv2
##from matplotlib import pyplot as plt
#
#img = cv2.imread('E5FLR3.png',0)
#
## Initiate FAST object with default values
#fast = cv2.FastFeatureDetector()
#
## find and draw the keypoints
#kp = fast.detect(img,None)
#img2 = cv2.drawKeypoints(img, kp, color=(255,0,0))
#
## Print all default params
#print "Threshold: ", fast.getInt('threshold')
#print "nonmaxSuppression: ", fast.getBool('nonmaxSuppression')
##print "neighborhood: ", fast.getInt('type')
#print "Total Keypoints with nonmaxSuppression: ", len(kp)
#
#cv2.imwrite('fast_true.png',img2)
#
## Disable nonmaxSuppression
#fast.setBool('nonmaxSuppression',0)
#kp = fast.detect(img,None)
#
#print "Total Keypoints without nonmaxSuppression: ", len(kp)
#
#img3 = cv2.drawKeypoints(img, kp, color=(255,0,0))
#
#cv2.imwrite('fast_false.png',img3)
#_________________________________________________________________________________
import cv2
import numpy as np

def detectLettersNoWalls(img):
    boundRect=[]
    img_gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #print img_gray
    cv2.imwrite('1.png',img_gray)
    #img_sobel = cv2.Sobel(img_gray, cv2.CV_8U, 1, 0, 3, 1, 0)
    img_sobel = cv2.Canny(img_gray,50,150,apertureSize = 3)
    #print img_sobel
    cv2.imwrite('2.png',img_sobel)
    retval, img_threshold = cv2.threshold(img_sobel, 0 ,255, cv2.THRESH_OTSU+cv2.THRESH_BINARY)
    #print img_threshold
    element = cv2.getStructuringElement(cv2.MORPH_RECT,(7,3))
    img_threshold = cv2.morphologyEx(img_threshold, cv2.MORPH_CLOSE, element)
    #print img_threshold
    contours, hierarchy = cv2.findContours(img_threshold,0,1)
    #print contours
    for contour in contours:
        if(contour.size > 100):
            approx = cv2.approxPolyDP(contour, 3, True)
            appRect = cv2.boundingRect(approx)
            if(appRect[2] <100 and appRect[3] <200):
                boundRect.append(appRect)
    
    return boundRect

def detectRooms(img):
    boundRect=[]
    img_gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #print img_gray
    cv2.imwrite('1.png',img_gray)
    #img_sobel = cv2.Sobel(img_gray, cv2.CV_8U, 1, 0, 3, 1, 0)
    img_sobel = cv2.Canny(img_gray,50,150,apertureSize = 3)
    #print img_sobel
    cv2.imwrite('2.png',img_sobel)
    retval, img_threshold = cv2.threshold(img_sobel, 0 ,255, cv2.THRESH_OTSU+cv2.THRESH_BINARY)
    #print img_threshold
    element = cv2.getStructuringElement(cv2.MORPH_RECT,(7,3))
    img_threshold = cv2.morphologyEx(img_threshold, cv2.MORPH_CLOSE, element)
    #print img_threshold
    contours, hierarchy = cv2.findContours(img_threshold,0,1)
    #print contours
    for contour in contours:
        if(contour.size > 100):
            approx = cv2.approxPolyDP(contour, 3, True)
            appRect = cv2.boundingRect(approx)
            if(appRect[2] < 30 or appRect[3] < 30):
                boundRect.append(appRect)
    
    return boundRect
            
    

    
    


img = cv2.imread('E5FLR3.png')

gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
edges = cv2.Canny(gray,50,150,apertureSize = 3,  L2gradient= True )
minLineLength = 50
maxLineGap =8
lines = cv2.HoughLinesP(edges,1,np.pi/180,100,minLineLength,maxLineGap)


boundRectsNoWalls = detectLettersNoWalls(img)
rooms = detectRooms(img)
print boundRectsNoWalls
for bound in boundRectsNoWalls:
    print bound
    cv2.rectangle(img, (bound[0], bound[1]), (bound[0]+bound[2], bound[1]+bound[3]),(0,255,0), 2)
for bound in rooms:
    cv2.rectangle(img, (bound[0], bound[1]), (bound[0]+bound[2], bound[1]+bound[3]),(0,0,255), 2)
    
#LINES CANNOT BE IN BOUNDRECTNOWALLS
#bound[0] = x
#bound[1] = y
#bound[2] = w
#bound[3] = h

for x1,y1,x2,y2 in lines[0]:
#    for bound in boundRectsNoWalls:
#        if(( not(x1 >= bound[0] and y1 >= bound[2]) and ( x1 <= bound[0]+bound[2] and y1<= bound[1]+bound[3] ) ) ):
    cv2.line(img,(x1,y1),(x2,y2),(255,255,0),2)


cv2.imwrite('yolo.png',img)

