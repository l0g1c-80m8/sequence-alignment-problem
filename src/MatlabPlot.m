%Data imported from src/datapoints/generated/out*.*.txt
btime = [0.148,0.67,2.149,7.365,18.157,26.397,64.725,119.103,157.136,151.143,376.547,630.382,803.78,1049.88,1416.22];
bmem = [651264,655360,708608,827392,856064,1110016,1523712,2048000,2715648,3506176,5459968,8024064,11063296,14639104,17174528];

etime = [0.17,1.276,4.035,13.781,31.097,47.512,119.988,220.16,305.637,289.596,750.159,1212.42,1551.7,2053.37,2806.62];
emem = [655360,696320,741376,802816,839680,851968,839680,937984,978944,974848,991232,1044480,1179648,1110016,1150976];

probsize = [16,64,128,256,384,512,768,1024,1280,1536,2048,2560,3072,3584,3968];

%plot(probsize, btime, probsize, etime)
%title("Plot of Time (ms) vs Problem Size")
%xlabel("Problem Size")
%ylabel("Time (ms)")
%legend({"Basic", "Efficient"}, "Location", "northwest");

plot(probsize, bmem, probsize, emem);
title("Plot of Max Memory Usage (bytes) vs Problem Size")
xlabel("Problem Size")
ylabel("Max Memory Usage (bytes)")
legend({"Basic", "Efficient"}, "Location", "northwest");