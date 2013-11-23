%------------------------------------------------------------------------
%view_orientation_image
%Displays the orientation image as a quiver plot
%usage:
%view_orientation(o)
%o - orientation image(obtained by fft_enhance_cubs.m or
%orientation_image_rao.m)
%
%Contact:
%   ssc5@eng.buffalo.edu
%   www.eng.buffalo.edu/~ssc5
%------------------------------------------------------------------------
function view_orientation_image(o)
    [h,w]   =   size(o);
    x       =   0:w-1;
    y       =   0:h-1;
    quiver(x,y,cos(o),sin(o)); 
    axis([0 w 0 h]),axis image, axis ij;
%end function view_orieintation_image