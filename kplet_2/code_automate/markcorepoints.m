function markcorepoints()
% use this function to manually mark the minutiae points. For your help it takes image from
% the core diectory where all the images have places having with automatic
% detected corepoint marked.

  %system('rm -r gTrouth'); system('mkdir gTrouth');
  fnames = dir(fullfile(strcat(pwd,'/sampleimages/'), '*.bmp')); % Files in data folder have extension .bmp
  numfids = length(fnames);

for i = 1:numfids
     i
     I = imread(strcat(pwd,'/sampleimages/',fnames(i).name)); imshow(I);hold on

     [y, x, butt] = ginput(2);
     plot(y,x,'g*','MarkerSize',3);  hold on
     y
     x
     butt
     k=size(butt,1)
     if(k==2)
        if (butt==2) break; end
	if(butt==1)
	      ff=fopen(strcat(pwd,'/',strtok(fnames(i).name,'.'),'_gt.txt'),'w');
	      fprintf(ff,'%d %d %d %d \n', floor(x(1)), floor(y(1)),floor(x(2)), floor(y(2)));
	      fclose(ff);
	else
	      fprintf(' Skipped');
	end
     else if(k==1)
             if (butt==2) break; end
	     if(butt==1)
	      ff=fopen(strcat(pwd,'/',strtok(fnames(i).name,'.'),'_gt.txt'),'w');
	      fprintf(ff,'%d %d \n', floor(x), floor(y));
	      fclose(ff);
	     else
		fprintf(' Skipped');
	     end
     end

end
     close all;
end