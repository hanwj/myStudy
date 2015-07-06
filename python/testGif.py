## 将gif图像每一帧拆成独立的位图 
def gif2images( filename, distDir = '.', type = 'bmp' ):
    if not os.path.exists(distDir):
        os.mkdir(distDir)
    print 'spliting', filename,
    im  = Image.open( filename )
    im.seek(0)  # skip to the second frame
    cnt = 0
    type = string.lower(type)
    mode = 'RGB'  # image modea
    if type == 'bmp' or type == 'png':
        mode = 'P'    # image mode 
    im.convert(mode).save(distDir+'/%d.'%cnt+type )
    cnt = cnt+1
    try:
        while 1:
            im.seek(im.tell()+1)
            im.convert(mode).save(distDir+'/%d.'%cnt+type)
            cnt = cnt+1
    except EOFError:
        pass # end of sequence
    white = (255,255,255)
    preIm = Image.open(distDir+'/%d.'%0+type).convert('RGB')
    size = preIm.size
    prePixs = preIm.load()
    for k in range (1,cnt):
        print '.',
        im = Image.open(distDir+'/%d.'%k+type).convert('RGB')
        pixs = im.load()
        for i in range(size[0]):
            for j in range(size[1]):
                if pixs[i,j] == white:
                    pixs[i,j] = prePixs[i,j]
        preIm = im
        prePixs = preIm.load()
        im.convert(mode).save(distDir+'/%d.'%k+type)
    print '\n', filename, 'has been splited to directory: [',distDir,']'
    return cnt      # 总帧数

##############################################################
if __name__ == '__main__':
    frames = gif2images('001@2x.gif',distDir='tmp',type='png')
