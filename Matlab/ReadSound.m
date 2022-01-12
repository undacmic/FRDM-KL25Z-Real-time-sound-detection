clear all
close all
clc
device = serialport("COM8", 115200);
x2 = 1:128;
y2 = 1:128;
p = bar(x2, y2)
xlim([0 128])
ylim([0 255])
xlabel('Index')
ylabel('Value')
p.XDataSource = 'x2';
p.YDataSource = 'y2';
while(true)
    data = read(device, 128, "uint8");
    x = diff(data);

    for t = 1:128
        x2(t) = t;
        y2(t) = data(t);
        if y2(t) < 50
            set(p,'FaceColor','g');
        end
        if y2(t) >= 50 && y2(t) <= 175
            set(p,'FaceColor','y');
        end
        if y2(t) > 175
            set(p,'FaceColor','r');
        end
    end
    refreshdata
    drawnow
end